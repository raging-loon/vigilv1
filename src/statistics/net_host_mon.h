#ifndef NET_HOST_MON_H
#define NET_HOST_MON_H
#include <stdint.h>
struct host_mon{
  int open_ports[64];
  uint32_t ip_addr;
};



#endif /* NET_HOST_MON_H */
