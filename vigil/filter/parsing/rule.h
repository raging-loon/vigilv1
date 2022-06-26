/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Foobar. 
    If not, see <https://www.gnu.org/licenses/>. 

*/



#ifndef RULE_H
#define RULE_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/socket.h>
#include "../../packets/ip_hdr.h"
#include "../../packets/tcp.h"
#include <regex.h>
#include "../../packets/icmp4.h"

/*
  *-*-*-*- rule.h -*-*-*-*
  @purpose define struct for rules
  struct rule_data;
    ==> data for rules, applications of rules and logging.
    - u_char pkt -> the actual packet
    - int pkt_len is required for the functions in packet_parser.c
*/


// $homenet -> $externalnet
#define FLOW_OUTWARD            69
// $externalnet -> $homenet
#define FLOW_INWARD             70
// $externalnet <> $homenet
// $any <> $any
#define FLOW_EITHER             71

#define EXTERNAL_NET            -1
#define  R_TCP    126
#define  R_UDP    127
#define  R_ICMP   128
#define  R_ALL    -1

//! @brief the struct for gathering data to be tested against rules
struct rule_data{
  unsigned char *pkt;
  char *src_ip_addr;
  char *dest_ip_addr;
  uint32_t srcip,destip;
  int flow;
  unsigned int src_port;
  unsigned int dest_port;
  int __protocol;
  unsigned int pkt_len; // psize;
  unsigned int dsize;
  bool encrypted;
  const struct sockaddr_in * src_socket;
  const struct sockaddr_in * dest_socket;
  const struct ip_hdr * ip_header;
  const struct __tcp * tcp_header;
  const struct __icmp4 * icmp_header;
  unsigned char tcp_flags[8]; 
  int is_established;
  // ^ needs to be seperate since it's not part of the __tcp 
};
//! @brief take the rule_data and test it by iterating through all of the rules in rules
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
  uint16_t ack;
  uint32_t seq;
  uint16_t res1;

};

struct r_raw_ip_data{
  bool tosset, ttlset, protoset;
  uint8_t tos;
  

  uint8_t ttl;
  uint8_t proto;
};

//! @brief the actual data for the rules
struct rule{
  uint32_t src, dest;
  int dest_port, src_port;
  int flow;
  unsigned int offset;

  int dsize;
  int d_operator;
  char rulename[24];
  int rule_type;
  int times_matched;
  char rule_target[255];
  int protocol;
  int port;
  bool noencrypt;
  int severity;
  char message[128];
  regex_t pcre;
  char pcrestr[128];
  bool uses_pcre;
  unsigned int num_targets[4];
  char * targets[4];
  char raw_target[128];
  int is_established;
  // int total_ports;
  int depth;
  struct r_tcp_data tcp_data;
  struct r_raw_ip_data ip_data;
  struct r_icmp_dataset icmp_data;

  
  bool(*pkt_parser)(const struct rule_data *, const struct rule *);
  void(*action)(const struct rule_data *, const struct rule *, int);
};


bool r_engine(const struct rule *, const struct rule_data *);
bool test_tcp_session_status(const struct rule * r, const struct rule_data * rdata);

#endif /* RULE_H */
