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
// #include <netinet/ip_icmp.h>
#include "decode/l3pktmgr.h"
#include <time.h>
#include "colors.h"
#include "decode/igmp_dsct.h"
#include "protocols.h"
#include "utils.h"
#include "decode/tcpmgr.h"
#include "logging.h"
#include "decode/udpmgr.h"
#include "nethdr/ip_hdr.h"
#include "nethdr/ip6hdr.h"
#include "nethdr/icmp4.h"
#include "decode/icmpdsct.h"
#include "print_utils.h"
#include "engine/rule/rule.h"
#include "engine/rule/packet_parser.h"
#include "globals.h"
#include "debug.h"
#include "engine/rule/flags.h"
#include "engine/spi.h"


//! @brief handle decoding for ipv6
//! @todo expand on this

void ipv4pktmgr(const unsigned char * pkt, const int len){
  struct ip_hdr * ip_header = (struct ip_hdr * )(pkt + ETH_HDR_SZ);
  struct rule_data rdata;
  // rdata.spi_pkt->src_port = 0;
  char src_ip[16];
  char dest_ip[16]; 
  rdata.destip = (uint32_t)ntohl(ip_header->daddr);
  rdata.srcip =  (uint32_t)ntohl(ip_header->saddr);
  // printf("%u | %u | %u:%u\n",rdata.srcip,homenetmask,rdata.srcip & homenetmask,homenet);
  uint32_t srcstatus = rdata.srcip & homenetmask;
  uint32_t dststatus = rdata.destip & homenetmask;
  // printf("%d\n",rdata.srcip &  homenet);
  if(srcstatus == homenet){
    rdata.flow = FLOW_OUTWARD;
    // printf("Outgoing packet\n");
  }

  else if(dststatus == homenet){
    rdata.flow = FLOW_INWARD;
    // printf("Incoming packet\n");
  } 
  else 
    rdata.flow = FLOW_EITHER;
  

  rdata.pkt_len = len;
  rdata.ip_header = ip_header;


  strncpy(dest_ip, (char*)ipv4_ntoa(ip_header->daddr),sizeof(dest_ip));
  strncpy(src_ip, (char*)ipv4_ntoa(ip_header->saddr),sizeof(src_ip));
   // init both addresses;
  
  // init_member((const char *)&dest_ip);
  // init_member((const char *)&src_ip);
  // 
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
      


  if(ip_header->frag_off == 0x0020 || ip_header->frag_off == 0x0102){
    printf("%sFragmented ",__FRAGMENTED);
    

    if(packet_print)
      printf("%s",__END_COLOR_STREAM);
    else 
      printf(" %s -> %s%s\n",src_ip,dest_ip,__END_COLOR_STREAM);
  }
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
      ip4_tcp_decode(pkt,&rdata,len);
      break;
    case 17:
      rdata.__protocol = R_UDP;
      ip4_udp_decode(pkt,&rdata,len);
      break;
    default:
      printf("IPv4 %s -> %s Protocol Number = %d\n",rdata.src_ip_addr,rdata.dest_ip_addr,ip_header->protocol);
      break;
  }
  // free(rdata.pkt);
  // free(rdata);
}
