#ifndef DNS_DISECT_H
#define DNS_DISECT_H
#include "../../filter/parsing/rule.h"
void dns_disect(const unsigned char *, const struct rule_data *);

char * get_dns_name(const char *);

#endif /* DNS_DISECT_H */