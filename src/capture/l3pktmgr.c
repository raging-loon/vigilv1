#include <stdio.h>
#include <pcap.h>
#include <netinet/ip6.h>
#include <netinet/ether.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/ip.h>
#include "l3pktmgr.h"
#include "protocols.h"
#include "../packets/ip6hdr.h"
#include "../utils.h"
#include "tcpmgr.h"
#include "udpmgr.h"

#include "icmpdsct.h"
void ipv6pktmgr(const unsigned char * pkt,const  struct pcap_pkthdr * pkt_hdr){
  struct ip6hdr * ipv6_hdr = (struct ip6hdr *)(pkt + sizeof(struct ethhdr) );
  char dest_ip6[134];
  char src_ip6[134];
  strncpy(src_ip6,inet6_ntoa(ipv6_hdr->srcaddr),sizeof(src_ip6));
  strncpy(dest_ip6,inet6_ntoa(ipv6_hdr->dstaddr),sizeof(dest_ip6));
  printf("IPv6 ");
  // printf("src=%p dst=%p",ipv6_hdr->srcaddr,ipv6_hdr->dstaddr);
  printf("src=%s dst=%s\n", 
                      src_ip6,dest_ip6);
  switch(ipv6_hdr->n_hdr){
    case 58:
    case 0:{
      ip6_icmp_decode(pkt);
      break;
    }
  }
}

void ipv4pktmgr(const unsigned char * pkt, const struct pcap_pkthdr * pkt_hdr){
  struct iphdr * ip_header = (struct iphdr * )(pkt + ETH_HDR_SZ);
  struct sockaddr_in src, dest;
  char dest_ip[128];
  char src_ip[128];
  memset(&src,0,sizeof(src));
  memset(&dest,0,sizeof(dest));
  src.sin_addr.s_addr = ip_header->saddr;
  dest.sin_addr.s_addr = ip_header->daddr;
  strncpy(dest_ip, inet_ntoa(dest.sin_addr),sizeof(dest_ip));
    strncpy(src_ip, inet_ntoa(src.sin_addr),sizeof(src_ip));
  
  switch(ip_header->protocol){
    case 1:{
        printf("IPv4 %s -> %s\n",
                  src_ip, dest_ip);
      ip4_icmp_decode(pkt);
      break;
    }
    case 6:
      ip4_tcp_decode(pkt,src_ip,dest_ip);
      break;
    case 17:
      ip4_udp_decode(pkt, src_ip, dest_ip);
      break;
  }
}