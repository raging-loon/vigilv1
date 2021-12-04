#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include "src/capture/pktmgr.h"
#include <signal.h>
#include "globals.h"
#include "main.h"
#include "src/statistics/ip_addr_stat.h"

struct ip_addr_counter ip_stats[256];
int ip_addr_stat_counter_len = -1;
char ip_addr[32];
int total_pkt_captured = 0;

int main(int argc, char **argv){
  
  signal(SIGINT,sigint_processor);
  signal(SIGSEGV,sigint_processor);
  if(argc == 1){
    printf("Need interface name\n");
    printf("dev: add help stuff here\n");
    exit(0);
  }
  // char * ip_addr = ""
  printf("Note to developer, remove hard coded IP address\n");
  strcpy(ip_addr,"10.108.32.227");
  char * iface_name = argv[1];
  char *dev = pcap_lookupdev(iface_name);
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
  pcap_loop(pcap_mgr,-1, pktmgr, NULL);

}

void sigint_processor(int signal){
  printf("\nCaught signal 2, exiting...\n");
  printf("Total Packets Caught: %d\n",total_pkt_captured);
  printf("Statistics\nIp address    Count\n-----------------\n");
  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    printf("%s\n\t\ttotal sent = %d\n\t\ttotal recv = %d"
          "\n\t\tTCP sent = %d\n\t\tTCP recv = %d\n\t\t"
          "UDP sent = %d\n\t\tUDP recv = %d\n\t\t"
          "ICMP sent = %d\n\t\tICMP recv = %d\n\n",
          ip_stats[i].ip_addr, ip_stats[i].total_sent,ip_stats[i].total_recv,
          ip_stats[i].tcp_sent, ip_stats[i].tcp_recv,ip_stats[i].udp_sent, ip_stats[i].udp_recv,
          ip_stats[i].icmp_sent,ip_stats[i].icmp_recv);
  }
  exit(EXIT_SUCCESS);
}