#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udpmgr.h"
#include <netinet/udp.h>
#include "protocols.h"
#include "../statistics/ip_addr_stat.h"
#include "../colors.h"
#include <arpa/inet.h>
#include "../../globals.h"
#include "../packets/ip_hdr.h"
#include "../filter/parsing/rule.h"
#include "../utils.h"
#include "protocols/dns_disect.h"
#include "../debug.h"

/*
  *-*-*-*- udpmgr.c -*-*-*-*
  @purpose Provide decoding for the UDP header
  void ip4_udp_decode(const unsigned char * pkt, struct rule_data * rdata,const struct pcap_pkthdr * pkt_hdr);
    ==> Decode the ports and print the packets information to the screen(if cmd args permit it)
    Apply rules via the rulemgr function(/src/filter/parsing/rule.c)
  @TODO: ADD IPV6 SUPPORT!
*/


void ip4_udp_decode(const unsigned char * pkt, struct rule_data * rdata,const struct pcap_pkthdr * pkt_hdr){

  struct udphdr * udp_header = (struct udphdr*)(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr));
  add_ip_addr_or_inc_counter(rdata->src_ip_addr,true,UDP);
  add_ip_addr_or_inc_counter(rdata->dest_ip_addr,false, UDP);
  unsigned int src_port, dest_port;
  src_port = (unsigned int)ntohs(udp_header->uh_sport);
  dest_port = (unsigned int)ntohs(udp_header->uh_dport);
  if(packet_print) {
    printf("%s",__UDP_REG);
    printf("IPv4 %s:%d -> %s:%d UDP\n",
        rdata->src_ip_addr,src_port,rdata->dest_ip_addr,dest_port);
    printf("%s",__END_COLOR_STREAM);
  }
  rdata->src_port = src_port;
  rdata->dest_port = dest_port;
    if(IS_PORT_DEST_SRC(src_port,dest_port,53)){
    dns_disect(pkt + 15 + sizeof(struct ip_hdr) + sizeof(udp_header),rdata); 
  }
  rulemgr(rdata);
  
}