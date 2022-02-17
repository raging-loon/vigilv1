/*!
 * @file l3pktmgr.c
 * @brief Handle Layer 3 decoding
 * @section LICENSE
 * 
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
 *
 */

#include <stdio.h>
#include <pcap.h>
#include <netinet/ip6.h>
#include <netinet/ether.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include "../packets/ip_hdr.h"
// #include <netinet/ip_icmp.h>
#include "l3pktmgr.h"
#include <time.h>
#include "../colors.h"
#include "protocols/igmp_dsct.h"
#include "protocols.h"
#include "../packets/ip6hdr.h"
#include "../utils.h"
#include "tcpmgr.h"
#include "../logging.h"
#include "udpmgr.h"
#include "../packets/icmp4.h"
#include "icmpdsct.h"
#include "../print_utils.h"
#include "../filter/parsing/rule.h"
#include "../filter/parsing/packet_parser.h"
#include "../../globals.h"
#include "../debug.h"
#include "../engine/flags.h"
#include "../engine/spi.h"

/*
  *-*-*-*- l3pktmgr.c -*-*-*-*
  @purpose Handle decoding of layer three protocols for ipv4 and ipv6
  void ipv6pktmgr(const unsigned char * pkt,const  struct pcap_pkthdr * pkt_hdr);
    ==> Decodes ipv6_hdr based on the size of the ethernet header and the 
        ipv6_hdr struct located in /src/packets/ip6hdr.h
    Can currently decode ICMPv6
    @TODO: Add support for TCP and UDP decoding and for rule_data
    @FIXME: Fix IGMP decoding as it relates to spi_pkt
  void ipv4pktmgr(const unsigned char * pkt, const struct pcap_pkthdr * pkt_hdr);
    ==> Decodes ipv4_hdr based on size of ethernet header and the ip_hdr located in 
        /src/packets/iphdr.h
    Can decode the following:
      - TCP --> pass data to tcpmgr(/src/capture/tcpmgr.c)
      - UDP --> pass data to udpmgr(/src/capture/udpmgr.c)
      - ICMP -> pass data to icmpdsct(/src/capture/icmpdsct.c)
    Members of the watchlist(/src/statistics/watchlist.h) are initiated here through the
    "init_member" function.

*/

void ipv6pktmgr(const unsigned char * pkt,const  struct pcap_pkthdr * pkt_hdr){
  struct ip6hdr * ipv6_hdr = (struct ip6hdr *)(pkt + sizeof(struct ethhdr) );
  char dest_ip6[134];

  char src_ip6[134];
  strncpy(src_ip6,inet6_ntoa(ipv6_hdr->srcaddr),sizeof(src_ip6));
  strncpy(dest_ip6,inet6_ntoa(ipv6_hdr->dstaddr),sizeof(dest_ip6));
  // printf("IPv6 ");
  // printf("src=%p dst=%p",ipv6_hdr->srcaddr,ipv6_hdr->dstaddr);
  // printf("src=%s dst=%s\n", 
                      // src_ip6,dest_ip6);
  switch(ipv6_hdr->n_hdr){
    case 58:
    case 0:{
      ip6_icmp_decode(pkt,src_ip6,dest_ip6);
      break;
    }
    default:
      printf("IPv6 %s -> %s Protocol Number = %d\n",src_ip6,dest_ip6,ipv6_hdr->n_hdr);
      break;
  }
}

void ipv4pktmgr(const unsigned char * pkt, const struct pcap_pkthdr * pkt_hdr){
  struct ip_hdr * ip_header = (struct ip_hdr * )(pkt + ETH_HDR_SZ);
  struct rule_data rdata;
  // rdata.spi_pkt->src_port = 0;
  char src_ip[16];
  char dest_ip[16]; 
  rdata.destip = ip_header->daddr;
  rdata.srcip = ip_header->saddr;

  if(ip_header->saddr & homenetmask == homenet)
    rdata.flow = FLOW_OUTWARD;
  else if(ip_header->daddr & homenetmask == homenet) 
    rdata.flow == FLOW_INWARD;
  else 
    rdata.flow == FLOW_EITHER;
  
  rdata.pkt_len = pkt_hdr->len;
  rdata.ip_header = ip_header;

  rdata.pkt_len = pkt_hdr->len;
  
  int base_data_size = pkt_hdr->len 
                     - ETH_HDR_SZ
                     - (((struct iphdr *)(pkt + ETH_HDR_SZ))->ihl * 4);

  strncpy(dest_ip, ipv4_ntoa(ip_header->daddr),sizeof(dest_ip));
  strncpy(src_ip, ipv4_ntoa(ip_header->saddr),sizeof(src_ip));
   // init both addresses;
  
  init_member((const char *)&dest_ip);
  init_member((const char *)&src_ip);
  
  if(is_blocked_ipv4((const char *)&dest_ip)){
    char blockedmsg[1024];
    sprintf(blockedmsg,"%s Found blocked ipv4 address(dest): %s\n",get_formated_time(),dest_ip);
    saprintf(blockedmsg);
  }
  if(is_blocked_ipv4((const char *)&src_ip)){
    char blockedmsg[1024];

    sprintf(blockedmsg,"%s Found blocked ipv4 address(src): %s\n",get_formated_time(), src_ip);
    saprintf(blockedmsg);
  }
  rdata.src_ip_addr = (char *)&src_ip;
  rdata.dest_ip_addr = (char *)&dest_ip;
      


  if(ip_header->flags == 0x0020 || ip_header->flags == 0x0102){
    printf("%sFragmented ",__FRAGMENTED);
    

    if(packet_print)
      printf("%s",__END_COLOR_STREAM);
    else 
      printf(" %s -> %s%s\n",src_ip,dest_ip,__END_COLOR_STREAM);
  }
  int data_size;
  switch(ip_header->protocol){
    case 1:{
      // printf("ipv4pktmgr: icmp\n");
      rdata.__protocol = R_ICMP;
      ip4_icmp_decode(pkt,&rdata);
      break;
    }
    case 2:
      // printf("IPv4 IGMP %s -> %s\n",src_ip,dest_ip);
    
      rdata.__protocol = R_ALL;
      total_conversations--;
      ip4_igmp_decode(pkt,rdata.src_ip_addr,rdata.dest_ip_addr);
      
      break;
    
    case 6:

      rdata.__protocol = R_TCP; 
      ip4_tcp_decode(pkt,&rdata,pkt_hdr);
      break;
    case 17:
      rdata.__protocol = R_UDP;
      ip4_udp_decode(pkt,&rdata,pkt_hdr);
      break;
    default:
      printf("IPv4 %s -> %s Protocol Number = %d\n",rdata.src_ip_addr,rdata.dest_ip_addr,ip_header->protocol);
      break;
  }
  // free(rdata.pkt);
  // free(rdata);
}
