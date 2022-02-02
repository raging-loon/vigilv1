#ifndef ENGINE_H
#define ENGINE_H

/*
  *-*-*-*- engine.h -*-*-*-*
  @purpose serve as the main place for suspicious traffic to be analyzed
  TODO: Figure out if rule.c will be replaced with a function in here
  TODO: 
*/

const enum{
  NA_IPv4 = 220,
  NA_IPv6 
};

struct net_addr{
  char netaddr[40];
  int addr_type;
};




typedef struct{
  const struct rule_data * rdata;
  
} tu_engine_data_t;
#include "../filter/parsing/rule.h"



void nshengine(const struct rule_data * );

void ne_portscan_bs_d(const struct rule_data *);
#endif /* ENGINE_H */