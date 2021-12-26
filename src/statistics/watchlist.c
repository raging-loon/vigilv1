#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "watchlist.h"
#include "../../globals.h"
#include "../utils.h"



bool tcp_portscan_detect(const struct watchlist_member * w){
  printf("%s:  %d\n",ipv4_ntoa(&w->ip_addr), w->rst_pkt_recv);
  int subtimes[20];
  int subtime_t = 0;
  for(int i = w->rst_pkt_recv - 1; i !=0;  ){
    // if(w->last_rst_pkt_times[i] == w->last_rst_pkt_times[0])  break;
    int temp = i;
    
    
    subtimes[subtime_t++] = w->last_rst_pkt_times[i] - w->last_rst_pkt_times[--i];
    if(temp == 1) break;
  }
  int f = 0;
  for(int i = 0; i < subtime_t; i++){
    if(subtimes[i] < 14843508) f++;
  }
  if(f > 5){
    printf("Portscan Detected from IP Address %s\n",ipv4_ntoa(&w->ip_addr));
  }
  
}



void member_ready_for_scan(){
  for(int i = 0; i < watchlist_num + 1;i++){
    const struct watchlist_member * w = &watchlist[i];
    if(w->rst_pkt_recv >= 20){
      tcp_portscan_detect(w);
    }
  }
}

int member_exists(uint32_t ip){
  int i = 0;
  for( ; i < watchlist_num + 1; i++){
    if(watchlist[i].ip_addr == ip) return i;
  }
  return -1;
}