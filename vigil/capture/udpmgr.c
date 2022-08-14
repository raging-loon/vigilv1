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
#include <stdlib.h>
#include <string.h>
#include "decode/udpmgr.h"
#include <netinet/udp.h>
#include "protocols.h"
#include "colors.h"
#include <arpa/inet.h>
#include "globals.h"
#include "nethdr/ip_hdr.h"
#include "engine/rule/rule.h"
#include "utils.h"
#include "decode/dns_disect.h"
#include "debug.h"

/*
  *-*-*-*- udpmgr.c -*-*-*-*
  @purpose Provide decoding for the UDP header
    ==> Decode the ports and print the packets information to the screen(if cmd args permit it)
    Apply rules via the rulemgr function(/src/filter/parsing/rule.c)
  @TODO: ADD IPV6 SUPPORT!
*/


void ip4_udp_decode(const unsigned char * pkt, struct rule_data * rdata, const int len){

  struct udphdr * udp_header = (struct udphdr*)(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr));
  
  rdata->pkt = (unsigned char *)(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr) + sizeof(udp_header));
  
  
  unsigned int src_port, dest_port;
  src_port = (unsigned int)ntohs(udp_header->uh_sport);
  dest_port = (unsigned int)ntohs(udp_header->uh_dport);
  if(packet_print) {
    printf("%s",__UDP_REG);
    printf("IPv4 %s:%d -> %s:%d UDP\n",
        rdata->src_ip_addr,src_port,rdata->dest_ip_addr,dest_port);
    printf("%s",__END_COLOR_STREAM);
  }
  rdata->src_port = src_port;
  rdata->dest_port = dest_port;
    if(IS_PORT_DEST_SRC(src_port,dest_port,53)){
    dns_disect(pkt + 15 + sizeof(struct ip_hdr) + sizeof(udp_header),rdata); 
  }
  rdata->dsize = len - ETH_HDR_SZ - sizeof(struct ip_hdr) - sizeof(udp_header);
  rulemgr(rdata);
  
}