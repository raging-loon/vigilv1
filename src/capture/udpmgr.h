#ifndef UDPMGR_H
#define UDPMGR_H
#include <pcap.h>
#include "../filter/parsing/rule.h"
void ip4_udp_decode(const unsigned char *,struct rule_data *,const struct pcap_pkthdr *);


#endif /* UDPMGR_H */