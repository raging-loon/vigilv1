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
#include <string.h>
#include "../packets/icmp6.h"
#include "../packets/ip6hdr.h"

#include <netinet/ip.h>
#include <netinet/icmp6.h>
#include "../packets/icmp4.h"
#include "protocols.h"
#include "../utils.h"
#include <time.h>
#include "../colors.h"
#include "icmpdsct.h"
#include "../globals.h"
#include "../config/rule.h"
#include "../engine/spi.h"
/*
  *-*-*-*- icmpdsct.c -*-*-*-*
  @purpose to decode ICMP packets
  ip6_icmp_decode(const u_char * pkt, const char * src, const char * dst);
  ip4_icmp_decode(const u_char * pkt, const char * src, const char * dst);
    ==> Decode ICMP packets by type and code. 
    Also will look at all hosts that have nmap_host_alive_watch and increment and detect based
    on the number of packets sent and whether or not the packet is a TIMESTAMP REQUEST or ECHO REQUEST
    @TODO: log and report ICMP abnormalties
    @TODO: look at more type/codes combos 
*/



void ip6_icmp_decode(const unsigned char * pkt,const char * src_ip,const char * dest_ip){
  
  struct __icmp6 * icmpv6 = (struct __icmp6 *)(pkt + ETH_HDR_SZ + sizeof(struct ip6hdr));
  if(packet_print){
    printf("%s",__REG_ICMP_v4_v6);
    printf("IPv6 %s -> %s\n",src_ip, dest_ip);
    printf("\tICMPv6 ");
    switch(icmpv6->icmp_type){
      case 0x85:{
        char src_mac[64];
        strncpy(src_mac,(char *)mac_ntoa(icmpv6->addr),sizeof(src_mac));
        printf(" Router Solicitation from %s\n",src_mac);
        break;
      }
      case 143:
        printf("Multicast Listener Report Message v2\n");
        break;
      case 130:
        printf("Multicast  Listener Query");
        break;
      case 135:
        printf("Neighbor Solicitation\n"); 
        break;
    }
    printf("%s",__END_COLOR_STREAM);
  }
}


void ip4_icmp_decode(const unsigned char * pkt,struct rule_data * rdata){
  // add_ip_addr_or_inc_counter(rdata->src_ip_addr,true,ICMP);
  // add_ip_addr_or_inc_counter(rdata->dest_ip_addr,false,ICMP);
  const char * const src_ip = rdata->src_ip_addr;
  const char * const dest_ip = rdata->dest_ip_addr;
  
  
  
  struct __icmp4 * icmp4 = (struct __icmp4 *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));

  rdata->pkt = (unsigned char *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));

  rdata->icmp_header = icmp4;
  rdata->dsize = rdata->pkt_len - ETH_HDR_SZ - sizeof(struct iphdr) - 8;

  rdata->__protocol = R_ICMP;
  rulemgr(rdata);

  if(packet_print) {
  printf("%s",__REG_ICMP_v4_v6);
  // printf("IPv4 ");
  printf("IPv4 %s -> %s\n",src_ip, dest_ip);
  printf("\tICMP ");
  switch(icmp4->type){
    case 0:
      printf(" echo reply\n");
      break;
    case 3:
      printf(" destination unreachable(");
      switch(icmp4->code){
        case 0:
          printf(" Network Unreachable )\n");
          break;
        case 1:
          printf(" Host Unreachable )\n");
          break;
        case 2:
          printf(" Protocol Unreachable )\n");
          break;
        case 3:
          printf(" Port Unreachable )\n");
          break;
        case 4:
          printf(" Fragmentation Needed )\n");
          break;
        case 5:
          printf(" Source Route Failed )\n");
          break;
        case 6:
          printf(" Destination Network Unreachable )\n");
          break;
        case 7:
          printf(" Destination Host Unreachable )\n");
          break;
        case 8:
          printf(" Source Host Isolated )\n");
          break;
        case 9:
          printf(" Network Administratively Prohibited )\n");
          break;
        case 10:
          printf(" Host Administratively Prohibited )\n");
          break;
        case 11:
          printf(" Network Unreachable for TOS )\n");
          break;
        case 12:
          printf(" Host Unreachable for TOS )\n");
          break;
        case 13:
          printf(" Communication Administratively Prohibited )\n");
          break;
        case 14:
          printf(" Host Precedence Violation )\n");
          break;
        case 15:
          printf(" Precedence Cutoff in Effect )\n");
          break;
        default:
          printf(" Unknown Code=%d )\n",icmp4->code);
          break;
      };
      break;
    case 4:
      printf(" Source Quench( flow control )\n");
      break;
    case 5:
      printf(" Redirect (");
      switch(icmp4->code){
        case 0:
          printf(" Redirect for Network )\n");
          break;
        case 1:
          printf(" Redirect for Host )\n");
          break;
        case 2:
          printf(" Redirect for TOS and Network )\n");
          break;
        case 3:
          printf(" Redirect for TOS and Host )\n");
          break;
        default:
          printf(" Unknown Code=%d )\n",icmp4->code);
          break;
      }

      break;
    case 8:
      printf(" echo request\n");
      break;
    case 9:
      if(icmp4->code == 0)
        printf(" Mobile IP Advertisement (Normal Router Advertisement ) )\n ");
      else
        printf(" Router Advertisement (Unknown Code: %d ) )\n",icmp4->code);
      break;
    case 10:
      printf(" Router Solicitation )\n");
      break;
    case 11:
      printf(" Time To Live exceeded");
      if(icmp4->code == 0)
        printf(" ( ttl exceeded in transit )\n");
      else if(icmp4->code == 1)
        printf(" ( Fragment Reassembly time exceeded )\n");
      else
        printf(" ( Unknown Code: %d)\n",icmp4->code);
      break;
    case 13:
      printf(" timestamp request\n");
      break;
    case 14:
      printf(" timestamp reply\n");
      break;
    default:
      printf(" unknown icmp type=%d",icmp4->type);
      break;
  }
    printf("%s",__END_COLOR_STREAM);
  }

}