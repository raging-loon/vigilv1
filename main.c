/*
 * Copyright 2021 Conner Macolley
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
 */

#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include "src/statistics/wclean.h"
#include "src/capture/pktmgr.h"
#include <signal.h>
#include "globals.h"
#include <getopt.h>
#include "main.h"
#include "src/filter/parsing/rule_parser.h"
#include "src/statistics/ip_addr_stat.h"
#include "src/rpc/nsh_server.h"
#include "src/statistics/watchlist.h"
#include <pthread.h>
#include "src/statistics/arpcache.h"
#include <time.h>

int main(int argc, char **argv){
  // rules/  = (struct rule *)malloc(sizeof(struct rule) * 128);
  is_running = 1;
  last_clean_time = (unsigned long)time(NULL);
  if(argc == 1){
    print_help_and_exit();
  }
  char error_buf[PCAP_ERRBUF_SIZE];
  char * iface_name;
  int opt;
  while((opt = getopt(argc,argv,"pdqhi:")) != -1){
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
      default:
        printf("Unknown argument -%c\n",opt);
        print_help_and_exit();
        break;
    }
  }
  
  signal(SIGINT,sigint_processor);
  signal(SIGSEGV,sigint_processor);  
  // char * ip_addr = "";
  deny_conf_parser("/etc/npsi/deny.conf");
  printf("Finsished loading explicit deny file(/etc/npsi/deny.conf)\n");
  
  if(load_csv_arp_cache() != -1) printf("Finished loading CSV arp cache\n");
  else printf("Failed to load CSV arp cache(non critical error)\n");
  

  char *dev = pcap_lookupdev(error_buf);
  printf("NPSI listening on interface %s\n",dev);
  pcap_t *pcap_mgr;
  rule_library_parser("/etc/npsi/npsi.conf");
  printf("Parsed rule files\n");
  if(dev == NULL){
    printf("Failure opening interface %s\n",iface_name);
    exit(EXIT_FAILURE);
  }
  char pkt_buffer[2046] = {0};
  pcap_mgr = pcap_open_live(dev,1024,1,100,pkt_buffer);
  if(pcap_mgr == NULL){
    perror("pcap_mgr in pcap_open_live");
    exit(EXIT_FAILURE);
  }
  start_nsh_server();
  printf("Unecrypted NSH config server started: 127.0.0.1:23\n");
  // start_wclean();
  pcap_loop(pcap_mgr,-1, pktmgr, NULL);
}

void sigint_processor(int signal){
  int is_running = 0;
  printf("\nCaught signal %d, exiting...\n",signal);
  perror("");
  if(!quiet_exit){

    printf("Total Packets Caught: %d\n",total_pkt_captured);
    printf("Statistics\nIp address    Count\n-----------------\n");
    for(int i = 0; i <= watchlist_num; i++){
      printf("%s\n\t\ttotal packets = %d\n\t\ttotal sent = %d\n\t\ttotal recv = %d"
            "\n\t\tTCP sent = %d\n\t\tTCP recv = %d\n\t\t"
            "UDP sent = %d\n\t\tUDP recv = %d\n\t\t"
            "ICMP sent = %d\n\t\tICMP recv = %d\n\n",
            watchlist[i].ip_addr,watchlist[i].count,watchlist[i].total_sent,watchlist[i].total_recv,
            watchlist[i].tcp_sent, watchlist[i].tcp_recv,watchlist[i].udp_sent, watchlist[i].udp_recv,
            watchlist[i].icmp_sent,watchlist[i].icmp_recv);
    }
    
  }
  FILE * fp = fopen("/usr/share/npsi/arpcache.csv","w");
  if(fp == NULL){
    printf("Cannot open /usr/share/npsi/arpcache.csv: printing arpcache to screen\n");
    fclose(fp);
    for(int i = 0; i < arp_entries + 1; i++){
      printf("%s -> %s\n",arpcache[i].ip_addr, arpcache[i].mac_addr);
    }
    exit(EXIT_SUCCESS);
  }
  for(int i = 0; i < arp_entries + 1; i++){
    fprintf(fp,"%s,%s\n",arpcache[i].ip_addr, arpcache[i].mac_addr);
  }
  fclose(fp);
  exit(EXIT_SUCCESS);
}




static void print_help_and_exit(){
  printf("NPSI UTM %s\n"
         "\t-d: debug mode\n"
         "\t-h: display this message\n"
         "\t-i <iface>: set the interface to listen on\n"
         "\t-p print packets\n"
         "\t-q exit quietly\n",VERSION);
  exit(EXIT_SUCCESS);
}