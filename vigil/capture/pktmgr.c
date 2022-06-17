/*
 * Copyright 2021-2022 Conner Macolley
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
// void pktmgr(unsigned char * interface, const int len, const unsigned char * pkt){
 ;
void pktmgr(unsigned char * user, struct  pcap_pkthdr * pkt_hdr, const unsigned char * pkt){ 
  // pps_monitor();
  int len = pkt_hdr->len;
  if(packet_print) printf("\033[90m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[m\n");
  /*
    pktmgr -> ethernet header -> protocol number -> protocol number header -> data
    pktmgr -> ethernet header -> protocol number -> ipv4 -> protocol number -> tcp -> data
  */
  total_pkt_captured++;
  struct ethhdr * ethernet_header = (struct ethhdr*)pkt;
  // printf("%s -> %s",uc_mac_ntoa(ethernet_header->h_source),uc_mac_ntoa(ethernet_header->h_dest));
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