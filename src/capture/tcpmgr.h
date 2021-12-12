#ifndef TCPMGR_H
#define TCPMGR_H
#include <pcap.h>
void ip4_tcp_decode(const unsigned char *,const char*,const char*,const struct pcap_pkthdr *);


#endif /* TCPMGR_H */