#ifndef RULE_H
#define RULE_H
#include <stdbool.h>



const enum{
  BIT_MATCH,
  // ANOMALY
} rule_type_t;

const enum{
  LOW,
  MODERATE,
  SEVERE,
  EXTREME,
  CRITICAL
} severity;

struct rule_data{
  char * src_ip_addr;
  char * dest_ip_addr;
  int src_port;
  int dest_port;
  int __protocol;
  const unsigned char * pkt;
  int pkt_len;
};

void rulemgr(const struct rule_data *);
/* rule parsing -----> packet capture -----> packet ----> iterate through all rule -----> apply rule parser function pointer -----> apply rule action function pointer */


struct rule{
  char rulename[16];
  int rule_type;
  char rule_target[128];
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};


#endif /* RULE_H */