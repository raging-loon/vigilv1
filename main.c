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

// globals defined in @globals.h
// config options
int strict_icmp_timestamp_req;
int strict_nmap_host_alive_check;

// counters

int total_pkt_captured = 0;
int ip_addr_stat_counter_len = -1;
int blk_ipv4_len = -1;
int num_rules = -1;
int watchlist_num = -1;
int arp_entries = -1;
int is_running;
unsigned long last_clean_time;
unsigned long clean_delay;
// info objects
struct ip_addr_counter ip_stats[256];
struct rule rules[128] = {0};// = (struct rule *)malloc(sizeof(struct rule) * 128);
struct blocked_ipv4 blocked_ipv4_addrs[32];
struct watchlist_member watchlist[128] = {0};
struct arp_entry arpcache[255];
char ip_addr[32];
bool debug_mode;
// default files
char * default_config = "/etc/npsi/npsi.conf";
char * def_log_file = "/var/log/npsi/siglog.log";
char * default_host_conf = "/etc/npsi/hosts.conf";





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
  while((opt = getopt(argc,argv,"dhi:")) != -1){
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
      default:
        printf("Unknown argument -%c\n",opt);
        print_help_and_exit();
        break;
    }
  }
  
  signal(SIGINT,sigint_processor);
  signal(SIGSEGV,sigint_processor);  
  // char * ip_addr = ""
  deny_conf_parser("/etc/npsi/deny.conf");
  load_csv_arp_cache();
  rule_library_parser("/etc/npsi/npsi.conf");
  printf("Note to developer, remove hard coded IP address\n");
  strcpy(ip_addr,"10.108.32.227");
  char *dev = pcap_lookupdev(error_buf);
  printf("NPSI listening on interface %s\n",dev);
  pcap_t *pcap_mgr;
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
  // start_wclean();
  pcap_loop(pcap_mgr,-1, pktmgr, NULL);
}

void sigint_processor(int signal){
  int is_running = 0;
  printf("\nCaught signal %d, exiting...\n",signal);
  perror("");
  printf("Total Packets Caught: %d\n",total_pkt_captured);
  printf("Statistics\nIp address    Count\n-----------------\n");
  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    printf("%s\n\t\ttotal packets = %d\n\t\ttotal sent = %d\n\t\ttotal recv = %d"
          "\n\t\tTCP sent = %d\n\t\tTCP recv = %d\n\t\t"
          "UDP sent = %d\n\t\tUDP recv = %d\n\t\t"
          "ICMP sent = %d\n\t\tICMP recv = %d\n\n",
          ip_stats[i].ip_addr,ip_stats[i].count,ip_stats[i].total_sent,ip_stats[i].total_recv,
          ip_stats[i].tcp_sent, ip_stats[i].tcp_recv,ip_stats[i].udp_sent, ip_stats[i].udp_recv,
          ip_stats[i].icmp_sent,ip_stats[i].icmp_recv);
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
         "\t-i <iface>: set the interface to listen on\n",VERSION);
  exit(EXIT_SUCCESS);
}