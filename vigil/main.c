/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

  The main function handles all of the following:
   - Loading the function map
   - Set signals for interrupts and crashes
   - Initialize the throughout monitor
   - Get CPU info(for cosmetics)
   - Gather ip addresses from the blacklist
   - Parse and store all of the rules
   - Initialize all of the rules
   - Start the VRMC server
   - Start the capture process
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
#include <execinfo.h>
#include "capture/tcpmgr.h"
#include "backtrace/backtrace.h"
#include "monitoring/monitoring.h"
#include <unistd.h>
#include "lua/lua_engine.h"

#ifdef PRE_RELEASE_TEST
# include "capture/loadpcap.h"
#endif
/**
 * Main function of course
 * Handles all of the following:
 *  - Check if user running is root
 *  - Check if the program name is correct
 *  - Load the function map for crashes/backtracing
 *  - Set signals for kill, segv, and ctrl-c
 *  - Print some cosmetics
 *  - Parse command line options
 *  - Initialize globals
 *  - Initialize Lua State
 *  - Parse black list
 *  - Parse main config file and all of the rules
 *  - Preprocess rules
 *  - Detect network interfaces
 *  - Start capture
 * 
 * @author Conner Macolley
 *
 */
int main(int argc, char **argv){
  if(getuid()){
    printf("Root priviles required to run this program\n");
    exit(-1);
  } 
  // if(strcmp(argv[0],PROG_NAME) != 0 ){
  //   printf("Incorrect program name %s. Please rename it to %s.\n",argv[0],PROG_NAME);
  //   exit(-1);
  // }
  load_fn_mem_map(); // load the functions in case crash happens early

  // set signals
  signal(SIGINT,sigint_processor);  // handle CTRL-C
  signal(SIGSEGV,crash_handler);    // handle segmentation faults
  signal(SIGKILL,sigint_processor); // handle killing

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

  // handle cmd args
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
        // TODO: Move or add default interfaces into 
        //       installation or configuration
        iface_name = optarg;
        break;
      case 'p':
        packet_print = true;
        break;
      case 'q':
        quiet_exit = true;
        break;
      case 'e':
        #ifndef PRE_RELEASE_TEST
          printf("RUNNING IN DEMONSTRATION MODE. YOU HAVE 10 SECONDS TO ABORT.\n");
          sleep(10);
        #endif
        demo_mode = true;
        break;
      case 't':
        #ifndef PRE_RELEASE_TEST
          printf("RUNNING IN TEST MODE. YOU HAVE 10 SECONDS TO ABORT.\n");
          sleep(10);
        #endif
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
  init_globals();
  l_init();
  deny_conf_parser("/etc/vigil/deny.conf");
  if(debug_mode)
    printf("Finsished loading explicit deny file(/etc/vigil/deny.conf)\n");
  
  // find the rules and store/parse them
  rule_library_parser("/etc/vigil/vigil.conf");
  printf("Parsed rule files\n");
  // preprocess rules by parsing regex/pcre/string
  rule_processor();

  #ifdef PRE_RELEASE_TEST
    if(!filename){
      loadpcap(filename);
      return 0;
    }
  #endif


  printf("VIGIL listening on interface %s\n",iface_name);
  
  
  // get our interfaces
  detect_interfaces();
  // start capture, will print error and exit if "iface_name" doesn't exist
  start_interface_cap(iface_name);
}

// handle CTRL-C nad kill
void sigint_processor(int signal){
  free_globals();
  l_destroy();
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
