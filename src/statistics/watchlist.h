#ifndef WATCHLIST_H
#define WATCHLIST_H
#include <stdbool.h>
#include <stdint.h>
// max time between RST packets 7442974


struct watchlist_member{
  const char * ip_addr;
  
  int rst_pkt_recv;
  int suspect_activity;
  unsigned long last_rst_pkt_times[20];
}; 


bool tcp_portscan_detect(const struct watchlist_member * );

void member_ready_for_scan();


int member_exists(const char *);
#endif /* WATCHLIST_H */
