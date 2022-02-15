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


#include "../statistics/ip_addr_stat.h"
#include "../statistics/ip_addr_stat.h"
#include "../statistics/watchlist.h"
#include "../filter/parsing/rule.h"
#include "../filter/parsing/rule.h"
#include "protocols/http_disect.h"
#include "protocols/ftp-disect.h"
#include "../packets/ip_hdr.h"
#include "../engine/flags.h"
#include "../print_utils.h"
#include "../packets/tcp.h"
#include "../../globals.h"
#include "../engine/spi.h"
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "protocols.h"
#include "../colors.h"
#include "../utils.h"
#include "../debug.h"
#include <stdbool.h>
#include <stdint.h>
#include "tcpmgr.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/*
  *-*-*-*- tcpmgr.c -*-*-*-*
  @purpose Provide decoding for TCP 
  void ip4_tcp_decode(const unsigned char * pkt,struct rule_data * rdata,const struct pcap_pkthdr *pkt_hdr);
    ==> Decode the TCP header in IPv4 Packets
    Data decoded:
      - Ports
      - Flags
      - TOS 
      - TTL 
    In this function, rst and fin port scans will be detected. If either of these flags are set,
    a series of instructions will figure out if the destination IP(rst) or the src(fin) should fo through the 
    tcp_rst_portscan_detect or the fin_rst_portscan_detect functions located in /src/statistics/watchlist.c

    Various part of the TCP and IP header are added to the rdata(struct rule_data) structure so rules can be 
    adequately applied via the rulemgr function(/src/filter/parsing/rule.c)
  @TODO: add support for IPv6(URGENT)
*/

void ip4_tcp_decode(const unsigned char * pkt,struct rule_data * rdata,const struct pcap_pkthdr *pkt_hdr){
  
  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr));
  // printf("56\n");
  rdata->pkt = pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr) + (tcp_hdr->doff * 4);
  rdata->pkt_len = rdata->pkt_len - ETH_HDR_SZ - sizeof(struct ip_hdr) - (tcp_hdr->doff * 4);
  const char * src_ip = rdata->src_ip_addr;
  const char * dest_ip = rdata->dest_ip_addr;
  add_ip_addr_or_inc_counter(src_ip,true,TCP);
  add_ip_addr_or_inc_counter(dest_ip,false, TCP);
  unsigned int dest_port,  src_port;
  int flags_set = 0;
  bool rst_set = false;
  bool ack_set = false;
  bool syn_set = false;
  bool fin_set = false;
  bool psh_set = false;
  memset(&rdata->tcp_flags,0,sizeof(rdata->tcp_flags));
  // uint16_t syn, ack, rst, fin, psh, urg;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
  rdata->dest_port = (unsigned int )ntohs(tcp_hdr->dest);

  rdata->src_port = src_port;
  if(packet_print){
    printf("%s",__TCP_COLOR_NS);
    printf("IPv4 %s:%d -> %s:%d\n",
                    src_ip, src_port, dest_ip, dest_port);
    printf("\tTCP [");
  // printf("[");
  

  } 
  if((uint16_t)ntohs(tcp_hdr->ack) != 0){
    if(packet_print) printf("%s ACK ",__TCP_ACK);
    ack_set = true;
    strcat(rdata->tcp_flags,"A");
    flags_set++;
  }  
  if((uint16_t)ntohs(tcp_hdr->fin) != 0){
    if(packet_print) printf("%s FIN ",__TCP_FIN);
    fin_set = true;
    strcat(rdata->tcp_flags,"F");
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->psh) != 0){
    if(packet_print) printf("%s PSH ",__TCP_PSH);
    flags_set++;
    strcat(rdata->tcp_flags,"P");
    psh_set = true;
  }
 
  if((uint16_t)ntohs(tcp_hdr->rst) != 0){
    if(packet_print) printf("%s RST ",__TCP_RST);
    rst_set = true;
    strcat(rdata->tcp_flags,"R");
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->syn) != 0){
    if(packet_print) printf("%s SYN ", __TCP_SYN);
    syn_set = true;
    strcat(rdata->tcp_flags,"S");
    flags_set++;
  }

  if((uint16_t)ntohs(tcp_hdr->urg) != 0){
    if(packet_print) printf("%s URG ",__TCP_URG);
    flags_set++;
    strcat(rdata->tcp_flags,"U");
  } 
  
  if(packet_print) {
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
  if(PSH_ACK_SET(psh_set,ack_set) && flags_set == 2){
    update_table(rdata);
  }
  else if(FIN_ACK_SET(fin_set,ack_set)){
    end_connection(rdata);
  }

  else if(syn_set && flags_set == 1){
    add_new_conversation(rdata);
  }
  else if(SYN_ACK_SET(syn_set,ack_set) && flags_set == 2){
    spi_ud_thw(rdata);
  }
  else if(ack_set && flags_set == 1){
    update_table(rdata);
  }
  
  if(rst_set == true){
    int watchlist_index;
    if((watchlist_index = member_exists(rdata->dest_ip_addr)) != -1){
      struct watchlist_member * w = &watchlist[watchlist_index];
      
      strcpy(w->ip_addr,rdata->dest_ip_addr);
      w->psds.basic_ps_ds.rst_pkt_times[w->psds.basic_ps_ds.rst_pkt_recv++] = (unsigned long )time(NULL); 
      if(w->psds.basic_ps_ds.rst_pkt_recv >= 30){
        w->psds.basic_ps_ds.rst_pkt_recv = 30;
        if(tcp_rst_portscan_detect(w)){
          w->psds.basic_ps_ds.rst_pkt_recv = 0;
          memset(&w->psds.basic_ps_ds.rst_pkt_times,0,sizeof(w->psds.basic_ps_ds.rst_pkt_times));
        }

          // printf("PORT SCAN DETECTED ");
      }
    } else {
      struct watchlist_member * w = &watchlist[++watchlist_num];
      // w->ip_addr = rdata->dest_ip_addr;
      strcpy(w->ip_addr,rdata->dest_ip_addr);
      w->psds.basic_ps_ds.rst_pkt_recv = 0;
      w->psds.basic_ps_ds.rst_pkt_times[w->psds.basic_ps_ds.rst_pkt_recv++] = (unsigned long)time(NULL);
    }

  }
  /* else if(fin_set){
    
    int watchlist_index;
    if((watchlist_index = member_exists(rdata->dest_ip_addr)) != -1){
      struct watchlist_member * w = &watchlist[watchlist_index];
      strcpy(w->ip_addr,rdata->dest_ip_addr);
      w->psds.fin_data_set.fin_pkt_times[w->psds.fin_data_set.fin_pkt_recv++] = (unsigned long)time(NULL);
      if(w->psds.fin_data_set.fin_pkt_recv >= 30){
        w->psds.fin_data_set.fin_pkt_recv = 30;
        if(fin_rst_portscan_detect(w)){
          w->psds.fin_data_set.fin_pkt_recv = 0;
          memset(&w->psds.fin_data_set.fin_pkt_times,0,sizeof(w->psds.fin_data_set.fin_pkt_times));
        }
      }
    } else {
        struct watchlist_member * w = &watchlist[++watchlist_num];
        strcpy(w->ip_addr,rdata->dest_ip_addr);
        w->psds.fin_data_set.fin_pkt_recv = 0;
        w->psds.fin_data_set.fin_pkt_times[w->psds.fin_data_set.fin_pkt_recv++] = (unsigned long)time(NULL);
    }
  }
  */

  if(strict_nmap_host_alive_check == true &&
     ((ack_set && IS_PORT_DEST_SRC(dest_port,src_port,80)) || 
     (syn_set && IS_PORT_DEST_SRC(dest_port,src_port,443) ))){
    // check which host is sending based on the port numbers
    const char * target_ip;
    if(dest_port > src_port) target_ip = dest_ip;
    else target_ip = src_ip;
    int watchlist_index;
    if((watchlist_index = member_exists(target_ip)) != -1 ){
      struct watchlist_member * w = &watchlist[watchlist_index];
      if(w->nmap_watch_host_alive_watch.tcp_syn_sent == 0 && w->nmap_watch_host_alive_watch.num_done == 1){
        w->nmap_watch_host_alive_watch.tcp_syn_sent = 1;
        w->nmap_watch_host_alive_watch.num_done++;
      } 
      else if(w->nmap_watch_host_alive_watch.tcp_ack_sent == 0 && w->nmap_watch_host_alive_watch.num_done == 2){
        w->nmap_watch_host_alive_watch.tcp_ack_sent = 1;
        w->nmap_watch_host_alive_watch.num_done++;
      } else {
        // do nothing, this host isn't suspect of a nmap host alive scan yet.
      }

    }
  }


  
  if(packet_print){
    if((PSH_ACK_SET(psh_set,ack_set) && !fin_set) && IS_PORT_DEST_SRC(dest_port,src_port,80)){
      http_disect(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr) + sizeof(struct __tcp) + 12,rdata);
    }
  }
  if(IS_PORT_DEST_SRC(dest_port,src_port,21)){
    ftp_disect(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr) + (tcp_hdr->doff * 4),rdata);
  }

  // if(packet_print)
  // ascii_hexdump(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr) + (tcp_hdr->doff * 4),
                // pkt_hdr->len - ETH_HDR_SZ - sizeof(struct ip_hdr) - (tcp_hdr->doff * 4));
  rdata->dsize = pkt_hdr->len - ETH_HDR_SZ - sizeof(struct ip_hdr) - (tcp_hdr->doff * 4);
  rulemgr(rdata);
}
