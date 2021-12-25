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
  unsigned char *pkt;
  char *src_ip_addr;
  char *dest_ip_addr;
  unsigned int src_port;
  unsigned int dest_port;
  int __protocol;
  int pkt_len;

};

struct blocked_ipv4{
  char ipv4_addr[18];
};


void rulemgr(const struct rule_data *);
/* rule parsing -----> packet capture -----> packet ----> iterate through all rule -----> apply rule parser function pointer -----> apply rule action function pointer */


struct rule{
  char rulename[16];
  int rule_type;
  int times_matched;
  char rule_target[128];
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};


#endif /* RULE_H */