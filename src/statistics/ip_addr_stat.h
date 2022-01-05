#ifndef __IP_ADDR_STAT_H
#define __IP_ADDR_STAT_H
#include <stdbool.h>

void add_ip_addr_or_inc_counter(const char *, bool, int );
static void *verify_ip_addr(void *);
typedef struct {
  bool is_src;
  int traffic_type;
  char __ip_addr[15];
  int pkt_len;
} aiaoic_args;


#endif /* __IP_ADDR_STAT_H */