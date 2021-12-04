#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udpmgr.h"
#include <netinet/udp.h>
#include "protocols.h"
#include "../statistics/ip_addr_stat.h"
#include "../colors.h"
#include <arpa/inet.h>
#include "../packets/ip_hdr.h"
void ip4_udp_decode(const unsigned char * pkt, const char * src_ip, const char * dest_ip){

  struct udphdr * udp_header = (struct udphdr*)(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr));
  add_ip_addr_or_inc_counter(src_ip,true,UDP);
  add_ip_addr_or_inc_counter(dest_ip,false, UDP);
  printf("%s",__UDP_REG);
  unsigned int src_port, dest_port;
  src_port = (unsigned int)ntohs(udp_header->uh_sport);
  dest_port = (unsigned int)ntohs(udp_header->uh_dport);
  printf("IPv4 %s:%d -> %s:%d UDP\n",
      src_ip,src_port,dest_ip,dest_port);
  printf("%s",__END_COLOR_STREAM);
}