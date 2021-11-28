#include <pcap.h>
#include <netinet/ether.h>
#include "pktmgr.h"
#include "protocols.h"
#include "l2pktmgr.h"
#include <stdio.h>
#include "l3pktmgr.h"
void pktmgr(unsigned char *user, const struct pcap_pkthdr *pkt_hdr, const unsigned char *pkt){
  printf("\033[90m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[m\n");
  /*
    pktmgr -> ethernet header -> protocol number -> protocol number header -> data
    pktmgr -> ethernet header -> protocol number -> ipv4 -> protocol number -> tcp -> data
  */
  struct ethhdr * ethernet_header = (struct ethhdr*)pkt;
  switch(ethernet_header->h_proto){
    case L2_ARP:
      arpdecode(pkt, pkt_hdr);
      break;
    case L3_IPV6:
      ipv6pktmgr(pkt, pkt_hdr);
      break;
    case L3_IPV4:
      ipv4pktmgr(pkt, pkt_hdr);
      break;
    default:
      printf("Unknown frame protocol number: %d\n",ethernet_header->h_proto);
      break;
      
  }
}