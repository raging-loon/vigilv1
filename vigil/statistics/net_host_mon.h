#ifndef NET_HOST_MON_H
#define NET_HOST_MON_H
#include <stdint.h>
struct host_mon{
  struct open_port open_ports[32];
  int ports_opened;
  uint32_t ip_addr;
};

struct open_port{
  unsigned int port_number;
  unsigned int protocol;
};


#endif /* NET_HOST_MON_H */
