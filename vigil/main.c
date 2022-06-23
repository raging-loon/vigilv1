/*!
 * @file main.c
 * @author Conner Macolley
 * @brief Start everything and start services
 * @section LICENSE
 * Copyright 2021-2022 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 * @section DESCRIPTION
 * The main function handles all of the following:
 *  - Loading the function map
 *  - Set signals for interrupts and crashes
 *  - Initialize the throughout monitor
 *  - Get CPU info(for cosmetics)
 *  - Gather ip addresses from the blacklist
 *  - Parse and store all of the rules
 *  - Initialize all of the rules
 *  - Collect Lua Scripts
 *  - Start the VRMC server
 *  - Start the capture process
 */
#include <stdio.h>

#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include "netif/netif.h"
#include "capture/pktmgr.h"
#include <signal.h>
#include "globals.h"
#include <getopt.h>
#include "main.h"
#include "filter/parsing/rule_parser.h"
#include "vrmc/vrmc.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>
#include "statistics/arpcache.h"
#include <time.h>
#include "netif/netif.h"
#include "filter/parsing/rule_init.h"
#include "debug.h"
#include "lua/lua_engine.h"
#include <execinfo.h>
#include "capture/tcpmgr.h"
#include "backtrace/backtrace.h"
#include "monitoring/monitoring.h"
#include <unistd.h>
#ifdef PRE_RELEASE_TEST
# include "capture/loadpcap.h"
#endif

// Main function of course
int main(int argc, char **argv){
  
  load_fn_mem_map();
  // set signals
  // handle CTRL-C
  signal(SIGINT,sigint_processor);
  // handle segmentation faults
  signal(SIGSEGV,crash_handler);
  
  #ifdef PRE_RELEASE_TEST
    char * filename;
    printf("Vigil prelease testing. "
           "If you see this and are in a production environment, "
           "please download the final release of Vigil found here: <url when applicable>\n");
  #endif
  print_logo();
  print_cpu_info(); // purely for cosmetics
  printf("Running as PID %d\n",getpid());
  pps_monitor(); // to set a baseline on the file number

  if(argc == 1){
    print_help_and_exit();

  }
  // TODO: move this
  char * iface_name;
  int opt;
  const char * optstring;
  #ifdef PRE_RELEASE_TEST
    optstring = "pdqhtei:f:";
  #else
    optstring = "pdqhtei:";
  #endif
  while((opt = getopt(argc,argv,optstring)) != -1){
    switch(opt){
      case 'd':
        debug_mode = true;
        break;
      case 'h':
        print_help_and_exit();
        break;
      case 'i':
        iface_name = optarg;
        break;
      case 'p':
        packet_print = true;
        break;
      case 'q':
        quiet_exit = true;
        break;
      case 'e':
        printf("RUNNING IN DEMONSTRATION MODE. YOU HAVE 10 SECONDS TO ABORT.\n");
        sleep(10);
        demo_mode = true;
        break;
      case 't':
        printf("RUNNING IN TEST MODE. YOU HAVE 10 SECONDS TO ABORT.\n");
        sleep(10);
        in_test_mode = true;  
        break;
      #ifdef PRE_RELEASE_TEST
      case 'f':
        printf("Got file\n");
        filename = optarg;
        break;
      #endif
      default:
        printf("Unknown argument -%c\n",opt);
        print_help_and_exit();
        break;
    }
  }
  
 
  deny_conf_parser("/etc/vigil/deny.conf");
  printf("Finsished loading explicit deny file(/etc/vigil/deny.conf)\n");
  
  
  rule_library_parser("/etc/vigil/vigil.conf");
  printf("Parsed rule files\n");
  rule_processor();
  #ifdef PRE_RELEASE_TEST

    loadpcap(filename);
    return 0;
  #endif


  printf("VIGIL listening on interface %s\n",iface_name);
  
  
  collect_scripts();
  
  // start_vrmc_server();
  printf("Unecrypted VRMC config server started: 127.0.0.1:641\n");
  
  detect_interfaces();
  start_interface_cap(iface_name);
}

// handle CTRL-C
void sigint_processor(int signal){
  free_iface();
  // char * time = get_formated_time();
  char time[255];
  cb_get_formatted_time(time);
  printf("\nCaught signal %d at %s, exiting...\n", signal, time );
  
  FILE * fp = fopen("/usr/share/vigil/arpcache.csv","w");
  if(fp == NULL){
    printf("Cannot open /usr/share/vigil/arpcache.csv: printing arpcache to screen\n");
    fclose(fp);
    for(int i = 0; i < arp_entries + 1; i++){
      printf("%s -> %s\n",arpcache[i].ip_addr, arpcache[i].mac_addr);
    }
    goto __exit;
  }
  for(int i = 0; i < arp_entries + 1; i++){
    fprintf(fp,"%s,%s\n",arpcache[i].ip_addr, arpcache[i].mac_addr);
  }
  fclose(fp);
  for(int i = 0; i < thread_count; i++){
    pthread_join(threads[i],NULL);
  }
  // free_keys();
  __exit:
    exit(EXIT_SUCCESS);
}




void print_help_and_exit(){
  printf("VIGIL UTM %s\n"
         "\t-d: debug mode\n"
         "\t-h: display this message\n"
         "\t-i <iface>: set the interface to listen on\n"
         "\t-p print packets\n"
         "\t-q exit quietly\n",VERSION);
  exit(EXIT_SUCCESS);
}


void print_cpu_info(){
  FILE * cpuinfo = fopen("/proc/cpuinfo","rb");
  char * line = 0;
  size_t sz = 0;
  int numcpus = 0;
  char to_print[512];
  memset(&to_print,0,sizeof(to_print));
  while(getdelim(&line,&sz,'\n',cpuinfo) != -1){
    if(strncmp("model name", line, 10) == 0){
      int loc = 0;
      for(int i = 0; i < strlen(line); i++){
        if(line[i] == ':'){
          loc = i;
          break;
        }
      }
      numcpus++;
      strcat(to_print,line + loc + 2);
    }
  }
  printf("Found %d cpus:\n%s",numcpus,to_print);
  free(line);
  fclose(cpuinfo);
}

void print_logo(){
  printf(
    "██    ██ ██  ██████  ██ ██\n"     
    "██    ██ ██ ██       ██ ██\n"     
    "██    ██ ██ ██   ███ ██ ██\n"     
    " ██  ██  ██ ██    ██ ██ ██\n"     
    "  ████   ██  ██████  ██ ███████\n"


  );
}
