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
#include <pcap.h>
#include <netinet/ether.h>
#include "pktmgr.h"
#include "protocols.h"
#include "l2pktmgr.h"
#include <stdio.h>
#include "../globals.h"
#include "../utils.h"
#include "../logging.h"
#include "l3pktmgr.h"
#include "ip6decode.h"
#include "../monitoring/monitoring.h"
#include "../netif/netif.h"
void pktmgr(const int len, const unsigned char * pkt){
  /*
    pktmgr -> ethernet header -> protocol number -> protocol number header -> data
    pktmgr -> ethernet header -> protocol number -> ipv4 -> protocol number -> tcp -> data
  */
  struct ethhdr * ethernet_header = (struct ethhdr*)pkt;
  #ifndef PRE_RELEASE_TEST
    // if this is compiled as an actual release, ignore loopback traffic
    if((unsigned int )ethernet_header->h_dest | 0x0){
      return;
    }
  #endif
  
  if(packet_print) printf("\033[90m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[m\n");
  total_pkt_captured++;
  switch(ethernet_header->h_proto){
    case L2_ARP:
    case L2_RARP:
      arpdecode(pkt, len);
      break;
    case L3_IPV6:
      ip6decode(pkt, len);
      break;
    case L3_IPV4:
      ipv4pktmgr(pkt, len);
      break;
    case 0x0090:
      loopback_ctp_decode(pkt);
      break;
    default:
      // lfprintf("/var/log/vigil/siglog.log","BAD-TRAFFIC Unknown Ethernt Frame Protocol Number",
              //  uc_mac_ntoa(ethernet_header->h_source),uc_mac_ntoa(ethernet_header->h_dest),-1,-1);
      break;
      
  }
}