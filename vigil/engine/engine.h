#ifndef ENGINE_H
#define ENGINE_H

/*
  *-*-*-*- engine.h -*-*-*-*
  @purpose serve as the main place for suspicious traffic to be analyzed
  TODO: Figure out if rule.c will be replaced with a function in here
  TODO: 
*/


#define NA_IPv4         220
#define NA_IPv6         221





#include "../filter/parsing/rule.h"



void nshengine(const struct rule_data * );

void ne_portscan_bs_d(const struct rule_data *);
#endif /* ENGINE_H */