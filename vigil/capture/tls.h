#ifndef TLS_H
#define TLS_H
#include "../filter/parsing/rule.h"
#include <stdbool.h>
#include <pcap.h>

void tls_decode(const unsigned char * pkt ,struct rule_data * rdata,const struct pcap_pkthdr * pkt_hdr);

void tlshandshake(const unsigned char *,struct rule_data *,const struct pcap_pkthdr *);


#endif /* TLS_H */