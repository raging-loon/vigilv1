#ifndef __IP_ADDR_STAT_H
#define __IP_ADDR_STAT_H
#include <stdbool.h>
struct ip_addr_counter{
  char ip_addr[15];
  int count;
  int tcp_sent;
  int udp_sent;
  int icmp_sent;
  int tcp_recv;
  int udp_recv;
  int icmp_recv;
  int unknown_sent;
  int unknown_recv;
  int total_recv;
  int total_sent;
  size_t sz_recv;
  size_t sz_sent;
};
void add_ip_addr_or_inc_counter(const char *, bool, int );
static void *verify_ip_addr(void *);
typedef struct {
  bool is_src;
  int traffic_type;
  char __ip_addr[15];
} aiaoic_args;


#endif /* __IP_ADDR_STAT_H */