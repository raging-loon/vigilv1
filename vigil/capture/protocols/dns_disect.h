#ifndef DNS_DISECT_H
#define DNS_DISECT_H
#include "../../filter/parsing/rule.h"
void dns_disect(const unsigned char *, const struct rule_data *);

void get_dns_name(const char *,char *);

#endif /* DNS_DISECT_H */