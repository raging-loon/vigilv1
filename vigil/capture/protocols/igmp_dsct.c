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

#include "../../packets/igmpv4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../protocols.h"
#include <netinet/ip.h>
#include "../../utils.h"
#include <netinet/ether.h>
#include "../../globals.h"
void ip4_igmp_decode(const unsigned char * pkt, const char * src_ip, const char * dest_ip){
  if(packet_print){
    struct main_igmp * type_decode = (struct main_igmp *)(pkt + sizeof(struct ethhdr) + sizeof(struct iphdr) + 4);
    
    printf("IPv4 IGMP %s -> %s [", src_ip ,dest_ip);
    switch(type_decode->type){
      case 0x11:{
        printf(" Membership Query ]\n");
        break;
      }
      case 0x22:{
        struct igmp_member_report * igmp_mem_rep = (struct igmp_member_report *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr) + 4);
  
        char multicast_ip[32];
        strcpy(multicast_ip,(char *)ipv4_ntoa(igmp_mem_rep->multicast_address));
        printf(" Membership Report / Join group %s for any sources ]\n",multicast_ip);
        break;
      } 
      default:
        printf("Unknown IGMP Type=%d ]\n",type_decode->type);
        break;
    } 
  }
}

