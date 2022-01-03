#ifndef RULE_H
#define RULE_H
#include <stdbool.h>
#include <stdint.h>
#include <sys/socket.h>

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

const enum {
  R_TCP = 126,
  R_UDP,
  R_ICMP,
  R_ALL
} protocols_t;


struct rule_data{
  unsigned char *pkt;
  char *src_ip_addr;
  char *dest_ip_addr;
  unsigned int src_port;
  unsigned int dest_port;
  int __protocol;
  
  int pkt_len;
  const struct sockaddr_in * src_socket;
  const struct sockaddr_in * dest_socket;

};

struct blocked_ipv4{
  char ipv4_addr[18];
};


void rulemgr(const struct rule_data *);
/* rule parsing -----> packet capture -----> packet ----> iterate through all rules -----> apply rule parser function pointer -----> apply rule action function pointer */


struct rule{
  char rulename[16];
  int rule_type;
  int times_matched;
  char rule_target[128];
  int protocol;
  int port;
  // int total_ports;
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};


#endif /* RULE_H */