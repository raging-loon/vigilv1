#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/statistics/ip_addr_stat.h"
#include <stdint.h>
#include <stdbool.h>
extern struct ip_addr_counter ip_stats[256];
extern int ip_addr_stat_counter_len;
extern char ip_addr[32];
extern int total_pkt_captured;

extern int npsi_mode;
const enum {
  ACTIVE_CAPTURE = 10,
  BKGROUND_LOGGING
  // IDS_MODE
  // IPS_MODE
  // STAT_MODE
} modes;


#endif /* GLOBALS_H */