#include <stdio.h>
#include <pcap.h>
#include <netinet/ip6.h>
#include <netinet/ether.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/ip.h>
#include "../packets/ip_hdr.h"
#include "l3pktmgr.h"
#include "../colors.h"
#include "protocols/igmp_dsct.h"
#include "protocols.h"
#include "../packets/ip6hdr.h"
#include "../utils.h"
#include "tcpmgr.h"
#include "udpmgr.h"
#include "../packets/icmp4.h"
#include "icmpdsct.h"
#include "../print_utils.h"
void ipv6pktmgr(const unsigned char * pkt,const  struct pcap_pkthdr * pkt_hdr){
  struct ip6hdr * ipv6_hdr = (struct ip6hdr *)(pkt + sizeof(struct ethhdr) );
  char dest_ip6[134];
  char src_ip6[134];
  strncpy(src_ip6,inet6_ntoa(ipv6_hdr->srcaddr),sizeof(src_ip6));
  strncpy(dest_ip6,inet6_ntoa(ipv6_hdr->dstaddr),sizeof(dest_ip6));
  // printf("IPv6 ");
  // printf("src=%p dst=%p",ipv6_hdr->srcaddr,ipv6_hdr->dstaddr);
  // printf("src=%s dst=%s\n", 
                      // src_ip6,dest_ip6);
  switch(ipv6_hdr->n_hdr){
    case 58:
    case 0:{
      ip6_icmp_decode(pkt,src_ip6,dest_ip6);
      break;
    }
    default:
      printf("IPv6 %s -> %s Protocol Number = %d\n",src_ip6,dest_ip6,ipv6_hdr->n_hdr);
      break;
  }
}

void ipv4pktmgr(const unsigned char * pkt, const struct pcap_pkthdr * pkt_hdr){
  struct ip_hdr * ip_header = (struct ip_hdr * )(pkt + ETH_HDR_SZ);
  struct sockaddr_in src, dest;
  char dest_ip[128];
  char src_ip[128];
  memset(&src,0,sizeof(src));
  memset(&dest,0,sizeof(dest));
  
  src.sin_addr.s_addr = ip_header->saddr;
  dest.sin_addr.s_addr = ip_header->daddr;
  strncpy(dest_ip, inet_ntoa(dest.sin_addr),sizeof(dest_ip));
  strncpy(src_ip, inet_ntoa(src.sin_addr),sizeof(src_ip));
  // printf("");
  // if(ip_header->frag_off)
  // printf("%d\n",ip_header->flags);
  if(ip_header->flags == 0x0020 || ip_header->flags == 0x0102)
    printf("%sFragmented%s ",__FRAGMENTED,__END_COLOR_STREAM);
  int data_size;
  switch(ip_header->protocol){
    case 1:{
        // printf("IPv4 %s -> %s\n",
                  // src_ip, dest_ip);
      ip4_icmp_decode(pkt,src_ip,dest_ip);
      data_size = pkt_hdr->len 
                - ETH_HDR_SZ
                - sizeof(ip_header)
                - sizeof(struct __icmp4);
      ascii_hexdump((pkt + data_size),pkt_hdr->len - data_size);
      break;
    }
    case 2:
      // printf("IPv4 IGMP %s -> %s\n",src_ip,dest_ip);
      ip4_igmp_decode(pkt, src_ip, dest_ip);

      break;
    
    case 6:
      ip4_tcp_decode(pkt,src_ip,dest_ip);
      break;
    case 17:
      ip4_udp_decode(pkt, src_ip, dest_ip);
      break;
    default:
      printf("IPv4 %s -> %s Protocol Number = %d\n",src_ip,dest_ip,ip_header->protocol);
      break;
  }
}