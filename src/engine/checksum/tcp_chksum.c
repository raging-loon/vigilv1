#include "tcp_chksum.h"
#include "../../packets/tcp.h"
#include "../../packets/ip_hdr.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
bool tcp_check_sum_passed(struct ip_hdr * ip_header, struct __tcp * tcp_hdr){
  unsigned long sum = 0;
  unsigned short tcp_len = ntohs(ip_header->tot_len) - (ip_header->ihl<<2); 
  // struct __tcp * tcp_hdr= (struct __tcp *)ippayload;
  const unsigned long recv_chksum = tcp_hdr->check;

  unsigned short * ippayload = (unsigned short *)&tcp_hdr;
  sum += (ip_header->saddr >> 16) & 0xffff;
  sum += (ip_header->saddr) & 0xffff;
  sum += (ip_header->daddr >> 16) & 0xffff;
  sum += (ip_header->daddr) & 0xffff;
  sum += htons(IPPROTO_TCP);
  sum += htons(tcp_len);

  tcp_hdr->check = 0x0000;
  while(tcp_len > 1){
    sum += *ippayload++;
    tcp_len -= 2;
  }
  if(tcp_len > 0){
    // padding
    sum += ((*ippayload)&htons(0xffff));
  }
  while(sum >> 16){
    sum = (sum & 0xffff) + (sum >> 16);
  }
  sum = ~sum;
  tcp_hdr->check = recv_chksum;
  printf("%02x -- %02x\n",ntohs(sum),ntohs(tcp_hdr->check));

  if(ntohs(sum) == ntohs(recv_chksum)) return true;
  return false;
  
}   