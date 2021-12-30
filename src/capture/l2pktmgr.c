#include <pcap.h>
#include <netinet/ether.h>
#include <net/if_arp.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "l2pktmgr.h"
#include "protocols.h"
#include "../utils.h"
#include "../colors.h"
#include "../packets/arp-hdr.h"
#include "../statistics/arpcache.h"
#include "../packets/ctp.h"
#include "../../globals.h"
void arpdecode(const unsigned char * pkt, const struct pcap_pkthdr * pkthdr){
  if(debug_mode) printf("%s",__ARP_BOTH);

  struct arp_hdr * arp = (struct arp_hdr *)(pkt + ETH_HDR_SZ);

  switch(arp->opcode){
    case 0x0100:
    case 6144:{ // request:
      // printf("arp request\n");
      char dest_ip[32];
      char src_ip[32];
      strncpy(dest_ip,u8_ipv4_ntoa((uint8_t *)&arp->dst_ip),sizeof(dest_ip));
      strncpy(src_ip,u8_ipv4_ntoa((uint8_t *)&arp->src_ip),sizeof(src_ip));

      if(!strncmp(src_ip,"0.0.0.0",5) ){
        if(debug_mode) printf("PROTO ARP: PROBE: Who has %s?\n",dest_ip);
        // break;
      } else {
        if(debug_mode) printf("PROTO ARP: Who is at %s? Tell %s\n",dest_ip, src_ip);
      }
      break;
    }

    case 0x0002:
    case 512:{ // reply
      // printf("arp reply\n");
      char src_mac[64];
      char src_ip[32];
      // char * src_mac = mac_ntoa((uint8_t)*arp->src_mac);
      strncpy(src_mac,mac_ntoa(arp->src_mac),sizeof(src_mac));
      strncpy(src_ip,u8_ipv4_ntoa((uint8_t *)&arp->src_ip),sizeof(src_ip));


      if(entry_exists((uint8_t*)&arp->src_ip,(uint8_t*)&arp->src_mac) != -1){
        printf("Hellod\n");
        compare_entries((uint8_t)arp->src_ip, (uint8_t)arp->src_mac);
      } else {
        add_entry((uint8_t*)&arp->src_ip,(uint8_t*)&arp->src_mac);
      }
      
      
      
      if(debug_mode) printf("PROTO ARP: REPLY: %s is at %s\n",src_ip,src_mac);
      break;
    }
    default:{
      printf("Unknown ARP opcode: %d\n",arp->opcode);
      break;
    }
  }
  printf("%s",__END_COLOR_STREAM);

}


void loopback_ctp_decode(const unsigned char * pkt){
  struct config_test_proto * ctp_data = (struct config_test_proto *)(pkt + ETH_HDR_SZ);
  struct ethhdr * ethernet_hdr = (struct ethhdr *)(pkt);
  char src_mac[24];
  char dest_mac[24];
  strncpy(src_mac, uc_mac_ntoa(ethernet_hdr->h_source), sizeof(src_mac));
  strncpy(dest_mac, uc_mac_ntoa(ethernet_hdr->h_dest),sizeof(dest_mac));
  if(debug_mode) printf("LOOP %s -> %s",src_mac,dest_mac);
  
  switch(ctp_data->relevant_func){
    case 1:
      if(debug_mode) printf(" REPLY \n");
      break;
    default:
      if(debug_mode) printf(" UNKNOWN LOOP FUNCTION:%d \n",ctp_data->relevant_func);
      break;
  }
}
