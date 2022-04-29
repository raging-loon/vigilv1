#ifndef TLS_H
#define TLS_H

#include <stdbool.h>

void tls_decode(const unsigned char *,struct rule_data *,const struct pcap_pkthdr *);


#endif /* TLS_H */