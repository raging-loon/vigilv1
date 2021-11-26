#include <pcap.h>
#include <netinet/ether.h>
#include <net/if_arp.h>
#include "l2pktmgr.h"
#include "../utils.h"
#include "../packets/arp-hdr.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
void arpdecode(const unsigned char * pkt, const struct pcap_pkthdr * pkthdr){
  const unsigned char * packet = (pkt + sizeof(struct ethhdr));
  struct arp_hdr * arp;
  memset(&arp,0, sizeof(arp));
  arp = (struct arp_hdr *)(packet);

  switch(arp->opcode){
    case 0x0100:
    case 6144:{ // request:
      // printf("arp request\n");
      
      char * src_ip = ipv4_ntoa((uint32_t)(arp->src_ip));
      char * dst_ip = ipv4_ntoa((arp->dst_ip));
      if(!strncmp(src_ip,"0.0.0.0",5) ){
        printf("PROTO ARP: PROBE: Who has %s?\n",dst_ip);
        // break;
      } else {
        printf("PROTO ARP: Who is at %s? Tell %s\n",dst_ip, src_ip);
      }
      break;
    }

    case 0x0002:
    case 512:{ // reply
      // printf("arp reply\n");
      char * src_mac = mac_ntoa((uint8_t)*arp->src_mac);
      char * src_ip = ipv4_ntoa(arp->src_ip);
      printf("PROTO ARP: REPLY: %s is at %s\n",src_ip,src_mac);
      break;
    }
    default:{
      printf("Unknown ARP opcode: %d\n",arp->opcode);
      break;
    }
  }
  
}