#ifndef RULE_H
#define RULE_H
#include <stdbool.h>
#include <stdint.h>
#include <sys/socket.h>


#define  R_TCP    126
#define  R_UDP    127
#define  R_ICMP   128
#define  R_ALL    129


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
  char rulename[24];
  int rule_type;
  int times_matched;
  char rule_target[128];
  int protocol;
  int port;
  char message[128];
  // int total_ports;
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};


#endif /* RULE_H */