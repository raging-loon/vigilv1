#include <stdio.h>
#include <string.h>
#include "../packets/icmp6.h"
#include "../packets/ip6hdr.h"
#include <netinet/ip.h>
#include <netinet/icmp6.h>
#include "../packets/icmp4.h"
#include "protocols.h"
#include "../utils.h"
#include "../colors.h"
#include "icmpdsct.h"
void ip6_icmp_decode(const unsigned char * pkt,const char * src_ip,const char * dest_ip){
  printf("%s",__REG_ICMP_v4_v6);
  struct __icmp6 * icmpv6 = (struct __icmp6 *)(pkt + ETH_HDR_SZ + sizeof(struct ip6hdr));
  printf("IPv6 %s -> %s\n",src_ip, dest_ip);
  printf("\tICMPv6 ");
  switch(icmpv6->icmp_type){
    case 0x85:{
      char src_mac[64];
      strncpy(src_mac,mac_ntoa(icmpv6->addr),sizeof(src_mac));
      printf(" Router Solicitation from %s\n",src_mac);
      break;
    }
    case 143:
      printf("Multicast Listener Report Message v2\n");
      break;
    case 130:
      printf("Multicast  Listener Query");
      break;
    case 135:
      printf("Neighbor Solicitation\n"); 
      break;
  }
  printf("%s",__END_COLOR_STREAM);
}

void ip4_icmp_decode(const unsigned char * pkt,const char * src_ip,const char * dest_ip){
  printf("%s",__REG_ICMP_v4_v6);
  struct __icmp4 * icmp4 = (struct __icmp4 *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));
  // printf("IPv4 ");
  printf("IPv4 %s -> %s\n",src_ip, dest_ip);
  printf("\tICMP ");
  switch(icmp4->type){
    case 0:
      printf(" echo reply\n");
      break;
    case 3:
      printf(" destination unreachable(");
      switch(icmp4->code){
        case 0:
          printf(" Network Unreachable )\n");
          break;
        case 1:
          printf(" Host Unreachable )\n");
          break;
        case 2:
          printf(" Protocol Unreachable )\n");
          break;
        case 3:
          printf(" Port Unreachable )\n");
          break;
        case 4:
          printf(" Fragmentation Needed )\n");
          break;
        case 5:
          printf(" Source Route Failed )\n");
          break;
        case 6:
          printf(" Destination Network Unreachable )\n");
          break;
        case 7:
          printf(" Destination Host Unreachable )\n");
          break;
        case 8:
          printf(" Source Host Isolated )\n");
          break;
        case 9:
          printf(" Network Administratively Prohibited )\n");
          break;
        case 10:
          printf(" Host Administratively Prohibited )\n");
          break;
        case 11:
          printf(" Network Unreachable for TOS )\n");
          break;
        case 12:
          printf(" Host Unreachable for TOS )\n");
          break;
        case 13:
          printf(" Communication Administratively Prohibited )\n");
          break;
        case 14:
          printf(" Host Precedence Violation )\n");
          break;
        case 15:
          printf(" Precedence Cutoff in Effect )\n");
          break;
      };
      break;
    case 4:
      printf(" Source Quench( flow control )\n");
      break;
    case 5:
      printf(" Redirect\n");
      break;
    case 8:
      printf(" echo request\n");
      break;
    case 11:
      printf(" Time To Live exceeded\n");
      break;
    case 13:
      printf(" timestamp request\n");
      break;
    case 14:
      printf(" timestamp reply\n");
      break;
    default:
      printf(" unknown icmp type=%d",icmp4->type);
      break;
  }
  printf("%s",__END_COLOR_STREAM);
}