#ifndef L3PKTMGR_H
#define L3PKTMGR_H
#include <pcap.h>

void ipv6pktmgr(const unsigned char *, const struct pcap_pkthdr *);
void ipv4pktmgr(const unsigned char *, const struct pcap_pkthdr *);
 

#endif /* L3PKTMGR_H */ 