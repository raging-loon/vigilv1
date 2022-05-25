#ifndef UDPMGR_H
#define UDPMGR_H
#include <pcap.h>
#include "../filter/parsing/rule.h"
void ip4_udp_decode(const unsigned char * pkt, struct rule_data * rdata, const int len);


#endif /* UDPMGR_H */