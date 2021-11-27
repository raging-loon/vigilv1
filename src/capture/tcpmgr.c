#include "tcpmgr.h"
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <stdio.h>
#include "protocols.h"
#include "../packets/tcp.h"
#include <stdint.h>
void ip4_tcp_decode(const unsigned char * pkt,const char* src_ip,const char* dest_ip){
  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));
  unsigned int dest_port,  src_port;
  // uint16_t syn, ack, rst, fin, psh, urg;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
  printf("IPv4 %s:%d -> %s:%d\n",
                  src_ip, src_port, dest_ip, dest_port);
  printf("\tTCP [ ");
  // printf("[");
  if((uint16_t)ntohs(tcp_hdr->syn) != 0)
    printf(" SYN ");
  if((uint16_t)ntohs(tcp_hdr->psh) != 0)
    printf(" PSH ");
  if((uint16_t)ntohs(tcp_hdr->urg) != 0)
    printf(" URG ");
  if((uint16_t)ntohs(tcp_hdr->rst) != 0)
    printf(" RST ");
  if((uint16_t)ntohs(tcp_hdr->fin) != 0)
    printf(" FIN ");
  if((uint16_t)ntohs(tcp_hdr->ack) != 0)
    printf(" ACK ");
  printf("]\n");
  //+
}
