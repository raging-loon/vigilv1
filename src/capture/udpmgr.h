#ifndef UDPMGR_H
#define UDPMGR_H
#include <pcap.h>
void ip4_udp_decode(const unsigned char *, const char *, const char *,const struct pcap_pkthdr *);


#endif /* UDPMGR_H */