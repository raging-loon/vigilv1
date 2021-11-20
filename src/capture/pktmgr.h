#ifndef PKTMGR_H
#define PKTMGR_H
#include <pcap.h>
void pktmgr(unsigned char *, const struct pcap_pkthdr *, const unsigned char *);


#endif /* PKTMGR_H */