#ifndef SPI_H
#define SPI_H

#include <stdint.h>

struct packet_seen{
  uint32_t src_ip;
  uint32_t dest_ip;
  int protocol;
  unsigned int src_port;
  unsigned int dest_port;
  unsigned int time_recv;
  int is_flagged;
};



#endif /* SPI_H */


