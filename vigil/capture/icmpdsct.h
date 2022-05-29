#ifndef ICMPDSCT_H
#define ICMPDSCT_H
#include "../filter/parsing/rule.h"
void ip6_icmp_decode(const unsigned char *, const char *,const char *);
 
void ip4_icmp_decode(const unsigned char * const,struct rule_data *);


#endif /* ICMPDSCT_H */