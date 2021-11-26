#ifndef PROTOCOLS_H
#define PROTOCOLS_H
#include <netinet/ether.h>
#define L2_ARP        1544
#define L3_IPV6       0xdd86
#define L3_IPV4       8

#define ETH_HDR_SZ      sizeof(struct ethhdr)
#endif /* PROTOCOLS_H */