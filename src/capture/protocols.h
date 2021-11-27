#ifndef PROTOCOLS_H
#define PROTOCOLS_H
#include <netinet/ether.h>
#include <netinet/ip.h>
#define L2_ARP        1544
#define L3_IPV6       0xdd86
#define L3_IPV4       8

#define ETH_HDR_SZ     sizeof(struct ethhdr)
#define IPv4_HDR_LN    sizeof(struct iphdr)

#endif /* PROTOCOLS_H */