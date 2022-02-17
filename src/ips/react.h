#ifndef REACT_H
#define REACT_H
#include "../filter/parsing/rule.h"
static __thread char pkt_bffr[2048];

void rxn_icmp_unreachable(const struct rule_data *);


#endif /* REACT_H */