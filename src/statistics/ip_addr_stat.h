#ifndef __IP_ADDR_STAT_H
#define __IP_ADDR_STAT_H
#include <stdbool.h>
struct ip_addr_counter{
  char ip_addr[24];
  int count;
};
void add_ip_addr_or_inc_counter(const char *);
static void *verify_ip_addr(void *);
typedef struct {
  char __ip_addr[24];
} aiaoic_args;


#endif /* __IP_ADDR_STAT_H */