#include <pcap.h>
#include <netinet/ether.h>
#include "pktmgr.h"
#include "protocols.h"
#include "l2pktmgr.h"
#include <stdio.h>
#include "../../globals.h"
#include "l3pktmgr.h"
#include "../statistics/wclean.h"

/*
  *-*-*-*- pktmgr.c -*-*-*-*
  @purpose Decode the ethernet header
  void pktmgr(unsigned char *user, const struct pcap_pkthdr *pkt_hdr, const unsigned char *pkt);
    ==> The function used in the pcap_loop function in /main.c
    @actions:
      1. Print the packet seperator
      2. Scan for watchlist cleaning(not yet implemented)
      3. Call decoding functions based on the protocol number in the ethernet header
    @TODO: fix the scan_for_clean function in /src/statistics/wclean.c
*/
void pktmgr(unsigned char *user, const struct pcap_pkthdr *pkt_hdr, const unsigned char *pkt){
  if(packet_print) printf("\033[90m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[m\n");
  /*
    pktmgr -> ethernet header -> protocol number -> protocol number header -> data
    pktmgr -> ethernet header -> protocol number -> ipv4 -> protocol number -> tcp -> data
  */
  total_pkt_captured++;
  pkt_counter++;
  // printf("%d\n",clean_delay_pkts);
  if(pkt_counter >= clean_delay_pkts){
    // printf("Here\n");
    pkt_counter = 0;
    // scan_for_clean();

  }
  struct ethhdr * ethernet_header = (struct ethhdr*)pkt;
  switch(ethernet_header->h_proto){
    case L2_ARP:
    case L2_RARP:
      arpdecode(pkt, pkt_hdr);
      break;
    case L3_IPV6:
      ipv6pktmgr(pkt, pkt_hdr);
      break;
    case L3_IPV4:
      ipv4pktmgr(pkt, pkt_hdr);
      break;
    case 0x0090:
      loopback_ctp_decode(pkt);
      break;
    default:
      printf("Unknown frame protocol number: %d\n",ethernet_header->h_proto);
      break;
      
  }
}