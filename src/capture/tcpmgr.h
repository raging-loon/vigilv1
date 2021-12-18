#ifndef TCPMGR_H
#define TCPMGR_H
#include <pcap.h>
#include "../filter/parsing/rule.h"
void ip4_tcp_decode(const unsigned char *,struct rule_data *,const struct pcap_pkthdr *);


#endif /* TCPMGR_H */