#ifndef TLS_H
#define TLS_H
#include "../filter/parsing/rule.h"
#include <stdbool.h>
#include <pcap.h>

void tls_decode(const unsigned char * pkt, struct rule_data * rdata, const int len);

void tlshandshake(const unsigned char * pkt, struct rule_data * rdata, const int len);


#endif /* TLS_H */