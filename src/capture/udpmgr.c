#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udpmgr.h"
#include <netinet/udp.h>
#include "protocols.h"
#include <arpa/inet.h>
void ip4_udp_decode(const unsigned char * pkt, const char * src_ip, const char * dest_ip){
  struct udphdr * udp_header = (struct udphdr*)(pkt + ETH_HDR_SZ + IPv4_HDR_LN);
  unsigned int src_port, dest_port;
  src_port = (unsigned int)ntohs(udp_header->uh_sport);
  dest_port = (unsigned int)ntohs(udp_header->uh_dport);
  printf("IPv4 %s:%d -> %s:%d UDP\n",
      src_ip,src_port,dest_ip,dest_port);
    
}