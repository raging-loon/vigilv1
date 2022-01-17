#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "../statistics/watchlist.h"
#include "../statistics/wldataset.h"
#include "../filter/parsing/rule.h"

struct w_tcp_session{
  unsigned int start;
  unsigned int end;
  unsigned int length;
  int progress;
  uint16_t end_flags;
};


struct pkt_spi{
  unsigned int dest_port;
  unsigned int src_port;
  char src_ip_addr[16];
  char dest_ip_addr[16];
  int l3_proto;
  unsigned int __time__;
  int l4_proto;
  int is_flagged;
  uint16_t flags;
  struct rule * rules[16];
};


struct spi_member{
  struct watchlist_member * w;
  unsigned int twh_completed;
  struct w_tcp_session tcp_sessions[50];
  struct brute_force_ds bf_dataset;
};



void add_pkt_data(const struct pkt_spi *);


void * spi_scan();
#endif /* SPI_H */


