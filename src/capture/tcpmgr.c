#include "tcpmgr.h"
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <stdio.h>
#include "../filter/parsing/rule.h"
// #include "../filter/parsing/"
#include "protocols.h"
#include "../packets/tcp.h"
#include "../colors.h"
#include <stdint.h>
#include "../statistics/ip_addr_stat.h"
#include <stdbool.h>
#include "../statistics/ip_addr_stat.h"
#include "../packets/ip_hdr.h"
#include <string.h>
#include "../filter/parsing/rule.h"
void ip4_tcp_decode(const unsigned char * pkt,struct rule_data * rdata,const struct pcap_pkthdr *pkt_hdr){
  
  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr));
  // printf("56\n");
  rdata->pkt = pkt;
  const char * src_ip = rdata->src_ip_addr;
  const char * dest_ip = rdata->dest_ip_addr;
  add_ip_addr_or_inc_counter(src_ip,true,TCP);
  add_ip_addr_or_inc_counter(dest_ip,false, TCP);
  printf("%s",__TCP_COLOR_NS);
  unsigned int dest_port,  src_port;
  int flags_set = 0;
    
  // uint16_t syn, ack, rst, fin, psh, urg;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
  printf("IPv4 %s:%d -> %s:%d\n",
                  src_ip, src_port, dest_ip, dest_port);
  printf("\tTCP [");
  // printf("[");
  if((uint16_t)ntohs(tcp_hdr->syn) != 0){
    printf("%s SYN ", __TCP_SYN);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->psh) != 0){
    printf("%s PSH ",__TCP_PSH);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->urg) != 0){
    printf("%s URG ",__TCP_URG);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->rst) != 0){
    printf("%s RST ",__TCP_RST);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->fin) != 0){
    printf("%s FIN ",__TCP_FIN);
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->ack) != 0){
    printf("%s ACK ",__TCP_ACK);
    flags_set++;
  }
  printf("%s",__TCP_COLOR_NS);
  printf("]\n");
  
  printf("%s",__END_COLOR_STREAM);
  if(flags_set > 3 || flags_set == 0){
    printf("%sSuspicious TCP Packet recieved: %d flags%s\n",__TCP_RST,flags_set,__END_COLOR_STREAM);
  }
  // printf("dsetp\n");
  rdata->dest_port = (unsigned int )ntohs(tcp_hdr->dest);
  // perror("");
  // printf("sdf\n");
  
  rdata->src_port = src_port;
  // printf("srcp\n");
  
  rulemgr(rdata);
  //+
  
}
