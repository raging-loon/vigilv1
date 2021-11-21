#include <pcap.h>
#include <netinet/ether.h>
#include <net/if_arp.h>
#include "l2pktmgr.h"
#include "../utils.h"
#include <stdio.h>
void arpdecode(const unsigned char * pkt, const struct pcap_pkthdr * pkthdr){
  const unsigned char * packet = (pkt + sizeof(struct ethhdr));
  struct arphdr * arp = (struct arphdr *)(packet);
  switch(arp->ar_op){
    case 0x0100:
    case 6144:{ // request:
      struct arpreq * request = (struct arpreq*)(packet);
      printf("arp request\n");
      char * buffer;
      char * mac_addr = mac_ntoa(request->a,buffer,sizeof(buffer));
      printf("From %s\n", mac_addr);    
      break;
    }

    case 0x0002:
    case 512:{ // reply
      printf("arp reply\n");
      break;
    }
    default:{
      printf("Unknown ARP opcode: %d\n",arp->ar_op);
      break;
    }
  }
  
}