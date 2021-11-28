#ifndef __IP_ADDR_STAT_H
#define __IP_ADDR_STAT_H
#include <stdbool.h>
struct ip_addr_counter{
  char ip_addr[16];
  int count;
};
void * add_ip_addr_or_inc_counter(const char *);
int verify_ip_addr(const char *);

#endif /* __IP_ADDR_STAT_H */ 