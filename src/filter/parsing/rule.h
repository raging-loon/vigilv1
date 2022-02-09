#ifndef RULE_H
#define RULE_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/socket.h>
#include "../../packets/ip_hdr.h"
#include "../../packets/tcp.h"
#include "../../packets/icmp4.h"

/*
  *-*-*-*- rule.h -*-*-*-*
  @purpose define struct for rules
  struct rule_data;
    ==> data for rules, applications of rules and logging.
    - u_char pkt -> the actual packet
    - int pkt_len is required for the functions in packet_parser.c
*/

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
  const struct ip_hdr * ip_header;
  const struct __tcp * tcp_header;
  const struct __icmp4 * icmp_header;
  unsigned char tcp_flags[8]; 
  // ^ needs to be seperate since it's not part of the __tcp 
};
void rulemgr(const struct rule_data *);

struct blocked_ipv4{
  char ipv4_addr[18];
};


/* rule parsing -----> packet capture -----> packet ----> iterate through all rules -----> apply rule parser function pointer -----> apply rule action function pointer */
struct r_icmp_dataset{
  bool typeset,codeset,seqset,idset;
  uint8_t type;
  uint8_t code;
  uint16_t seq;
  uint16_t id;
};

struct r_tcp_data{
  bool flagset, ackset,seqset;
  unsigned char flags[8];
  uint32_t ack;
  uint32_t seq;
  uint16_t res1;

};

struct r_raw_ip_data{
  bool tosset, ttlset, protoset;
  uint8_t tos;
  

  uint8_t ttl;
  uint8_t proto;
};

struct rule{
  char rulename[24];
  int rule_type;
  int times_matched;
  char rule_target[128];
  int protocol;
  int port;
  int severity;
  char message[128];


  unsigned int num_targets[4];
  char * targets[4];
  
  
  // int total_ports;
  struct r_tcp_data tcp_data;
  struct r_raw_ip_data ip_data;
  struct r_icmp_dataset icmp_data;

  
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};


bool r_engine(const struct rule *, const struct rule_data *);


#endif /* RULE_H */