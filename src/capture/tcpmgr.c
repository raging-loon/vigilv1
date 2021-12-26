#include "../statistics/ip_addr_stat.h"
#include "../statistics/ip_addr_stat.h"
#include "../statistics/watchlist.h"
#include "../filter/parsing/rule.h"
#include "../filter/parsing/rule.h"
#include "../packets/ip_hdr.h"
#include "../packets/tcp.h"
#include "../../globals.h"
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "protocols.h"
#include "../colors.h"
#include "../utils.h"
#include <stdbool.h>
#include <stdint.h>
#include "tcpmgr.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void ip4_tcp_decode(const unsigned char * pkt,struct rule_data * rdata,const struct pcap_pkthdr *pkt_hdr){
  
  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr));
  // printf("56\n");
  rdata->pkt = pkt;
  const char * src_ip = rdata->src_ip_addr;
  const char * dest_ip = rdata->dest_ip_addr;
  add_ip_addr_or_inc_counter(src_ip,true,TCP);
  add_ip_addr_or_inc_counter(dest_ip,false, TCP);
  unsigned int dest_port,  src_port;
  int flags_set = 0;
  bool rst_set = false;
  // uint16_t syn, ack, rst, fin, psh, urg;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
  if(debug_mode){
    printf("%s",__TCP_COLOR_NS);
    printf("IPv4 %s:%d -> %s:%d\n",
                    src_ip, src_port, dest_ip, dest_port);
    printf("\tTCP [");
  // printf("[");
  }
  if((uint16_t)ntohs(tcp_hdr->syn) != 0){
    if(debug_mode) printf("%s SYN ", __TCP_SYN);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->psh) != 0){
    if(debug_mode) printf("%s PSH ",__TCP_PSH);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->urg) != 0){
    if(debug_mode) printf("%s URG ",__TCP_URG);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->rst) != 0){
    if(debug_mode) printf("%s RST ",__TCP_RST);
    rst_set = true;
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->fin) != 0){
    if(debug_mode) printf("%s FIN ",__TCP_FIN);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->ack) != 0){
    if(debug_mode) printf("%s ACK ",__TCP_ACK);
    flags_set++;
  }
  if(debug_mode) {
    printf("%s",__TCP_COLOR_NS);
    printf("]\n");
    printf("%s",__END_COLOR_STREAM);
  }
  if(flags_set > 3 || flags_set == 0){
    printf("%sSuspicious TCP Packet encoutered: %s:%d -> %s:%d, %d flags%s\n",
    __TCP_RST, 
    src_ip,
    src_port,
    dest_ip,
    dest_port,
    flags_set,
    __END_COLOR_STREAM);
  }


  if(rst_set == true){
    int watchlist_index;
    if((watchlist_index = member_exists(rdata->dest_ip_addr)) != -1){
      struct watchlist_member * w = &watchlist[watchlist_index];
      w->ip_addr = rdata->dest_ip_addr;
      w->last_rst_pkt_times[w->rst_pkt_recv++] = (unsigned long )time(NULL); 
      if(w->rst_pkt_recv >= 20){
        w->rst_pkt_recv = 20;
        if(tcp_portscan_detect(w)){

          w->rst_pkt_recv = 0;
          memset(&w->last_rst_pkt_times,0,sizeof(w->last_rst_pkt_times));
        }

          // printf("PORT SCAN DETECTED ");
      }
    } else {
      struct watchlist_member * w = &watchlist[++watchlist_num];
      w->ip_addr = rdata->dest_ip_addr;
      w->rst_pkt_recv = 0;
      w->last_rst_pkt_times[w->rst_pkt_recv++] = (unsigned long)time(NULL);
    }
  }


  // printf("dsetp\n");
  rdata->dest_port = (unsigned int )ntohs(tcp_hdr->dest);
  // perror("");
  // printf("sdf\n");
  
  rdata->src_port = src_port;
  // printf("srcp\n");
  
  rulemgr(rdata);
  //+
  
}
