#include "tcpmgr.h"
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <stdio.h>
#include "protocols.h"
#include "../packets/tcp.h"
#include "../colors.h"
#include <stdint.h>
#include "../statistics/ip_addr_stat.h"
#include <stdbool.h>
#include "../statistics/ip_addr_stat.h"
#include "../packets/ip_hdr.h"
void ip4_tcp_decode(const unsigned char * pkt,const char* src_ip,const char* dest_ip){
  add_ip_addr_or_inc_counter(src_ip);
  add_ip_addr_or_inc_counter(dest_ip);
  printf("%s",__TCP_COLOR_NS);
  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr));
  unsigned int dest_port,  src_port;
  
  bool syn_set;
  bool ack_set;
  bool rst_set;
    
    
  // uint16_t syn, ack, rst, fin, psh, urg;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
  printf("IPv4 %s:%d -> %s:%d\n",
                  src_ip, src_port, dest_ip, dest_port);
  printf("\tTCP [");
  // printf("[");
  if((uint16_t)ntohs(tcp_hdr->syn) != 0)
    printf("%s SYN ", __TCP_SYN);
  if((uint16_t)ntohs(tcp_hdr->psh) != 0)
    printf("%s PSH ",__TCP_PSH);
  if((uint16_t)ntohs(tcp_hdr->urg) != 0)
    printf("%s URG ",__TCP_URG);
  if((uint16_t)ntohs(tcp_hdr->rst) != 0)
    printf("%s RST ",__TCP_RST);
  if((uint16_t)ntohs(tcp_hdr->fin) != 0)
    printf("%s FIN ",__TCP_FIN);
  if((uint16_t)ntohs(tcp_hdr->ack) != 0)
    printf("%s ACK ",__TCP_ACK);
  printf("%s",__TCP_COLOR_NS);
  printf("]\n");
  
  printf("%s",__END_COLOR_STREAM);

  //+
  
}
