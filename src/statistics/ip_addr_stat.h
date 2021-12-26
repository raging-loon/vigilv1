#ifndef __IP_ADDR_STAT_H
#define __IP_ADDR_STAT_H
#include <stdbool.h>
struct ip_addr_counter{
  char ip_addr[15];
  unsigned int count;
  unsigned int tcp_sent;
  unsigned int udp_sent;
  unsigned int icmp_sent;
  unsigned int tcp_recv;
  unsigned int udp_recv;
  unsigned int icmp_recv;
  unsigned int unknown_sent;
  unsigned int unknown_recv;
  unsigned int total_recv;
  unsigned int total_sent;
  unsigned int sz_recv;
  unsigned int sz_sent;
};
void add_ip_addr_or_inc_counter(const char *, bool, int );
static void *verify_ip_addr(void *);
typedef struct {
  bool is_src;
  int traffic_type;
  char __ip_addr[15];
  int pkt_len;
} aiaoic_args;


#endif /* __IP_ADDR_STAT_H */