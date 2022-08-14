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
#include "ip6decode.h"
#include "../packets/ip6hdr.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../config/rule.h"
#include <netinet/ether.h>
#include "icmpdsct.h"
#include <arpa/inet.h>
#include "../globals.h"
#include "../utils.h"

void ip6decode(const unsigned char * pkt,const  int len){
  struct ip6hdr * ipv6_hdr = (struct ip6hdr *)(pkt + sizeof(struct ethhdr) );
  char dest_ip6[41];

  char src_ip6[41];
  strncpy(src_ip6, (char *)inet6_ntoa(ipv6_hdr->srcaddr),sizeof(src_ip6));
  strncpy(dest_ip6,(char *)inet6_ntoa(ipv6_hdr->dstaddr),sizeof(dest_ip6));
  // printf("IPv6 ");
  // printf("src=%p dst=%p",ipv6_hdr->srcaddr,ipv6_hdr->dstaddr);
  // printf("src=%s dst=%s\n", 
                      // src_ip6,dest_ip6);
  // struct rule_data rdata;
  switch(ipv6_hdr->n_hdr){
    case 0:{
      ip6_icmp_decode(pkt,src_ip6,dest_ip6);
      break;
    }
    default:
      if(packet_print)
      printf("IPv6 %s -> %s Protocol Number = %d\n",src_ip6,dest_ip6,ipv6_hdr->n_hdr);
      break;
  }
}