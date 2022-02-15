/*!
 * @file
 * @brief Handle ICMP decoding for IPv4 and IPv6
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
 * @section DESCRIPTION
 * Handle ICMP decoding for IPv4 and IPv6
 */

#include <stdio.h>
#include <string.h>
#include "../packets/icmp6.h"
#include "../packets/ip6hdr.h"
#include "../statistics/ip_addr_stat.h"

#include <netinet/ip.h>
#include <netinet/icmp6.h>
#include "../statistics/watchlist.h"
#include "../packets/icmp4.h"
#include "protocols.h"
#include "../utils.h"
#include <time.h>
#include "../colors.h"
#include "icmpdsct.h"
#include "../../globals.h"
#include "../filter/parsing/rule.h"
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
        strncpy(src_mac,mac_ntoa(icmpv6->addr),sizeof(src_mac));
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
  add_ip_addr_or_inc_counter(rdata->src_ip_addr,true,ICMP);
  add_ip_addr_or_inc_counter(rdata->dest_ip_addr,false,ICMP);
  const char * src_ip = rdata->src_ip_addr;
  const char * dest_ip = rdata->dest_ip_addr;
  
  
  
  struct __icmp4 * icmp4 = (struct __icmp4 *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));
  rdata->pkt = (pkt + ETH_HDR_SZ + sizeof(struct iphdr));
  rdata->icmp_header = icmp4;
  int len = rdata->pkt_len;
  rdata->dsize = rdata->pkt_len - ETH_HDR_SZ - sizeof(struct iphdr) - 8;
  if(icmp4->type == 8 && strict_nmap_host_alive_check == true){
    int watchlist_index;
    if((watchlist_index = member_exists(rdata->src_ip_addr)) != -1){
      struct watchlist_member * w = &watchlist[watchlist_index];
      if(w->nmap_watch_host_alive_watch.num_done == 0){
        w->nmap_watch_host_alive_watch.start_time = (unsigned long)time(NULL);
        w->nmap_watch_host_alive_watch.icmp_echo_sent = 1;
        w->nmap_watch_host_alive_watch.num_done++;
      } 
    } else {
      struct watchlist_member * w = &watchlist[++watchlist_num];
      strcpy(w->ip_addr,src_ip);
      w->nmap_watch_host_alive_watch.start_time = (unsigned long)time(NULL);
      w->nmap_watch_host_alive_watch.icmp_echo_sent = 1;
      w->nmap_watch_host_alive_watch.num_done++;
    }
    
  } else if(icmp4->type == 13 && (strict_icmp_timestamp_req == true || strict_nmap_host_alive_check == true)){
    if(strict_icmp_timestamp_req){
      printf("Time stamp request: %s -> %s(config specifies strict timestamp alerts)\n",src_ip,dest_ip);
    }
    if(strict_nmap_host_alive_check){
      int watchlist_index;
      if((watchlist_index = member_exists(src_ip)) != -1){
        struct watchlist_member * w = &watchlist[watchlist_index];
        if(w->nmap_watch_host_alive_watch.num_done != 3) goto stop;
        else {
          w->nmap_watch_host_alive_watch.end_time = (unsigned long)time(NULL);
          if(w->nmap_watch_host_alive_watch.end_time - w->nmap_watch_host_alive_watch.start_time <= 308450){  
            printf("Possible nmap host alive check %s -> %s; matched ICMP Echo, TCP SYN, TCP ACK, and ICMP Timestamp request\n",src_ip,dest_ip);
            FILE * fp = fopen(def_log_file,"a");
            char logmessage[180];
            sprintf(logmessage,"Possible nmap host alive check %s -> %s at %s; matched ICMP Echo, TCP SYN, TCP ACK, and ICMP Timestamp request\n",src_ip,dest_ip,get_formated_time());
            fputs(logmessage,fp);
            fclose(fp);
            memset(&w->nmap_watch_host_alive_watch,0,sizeof(w->nmap_watch_host_alive_watch));
          }
        }
      }
    }
  }
  stop:;
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