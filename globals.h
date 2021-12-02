#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/statistics/ip_addr_stat.h"

extern struct ip_addr_counter ip_stats[256];
extern int ip_addr_stat_counter_len;
extern char ip_addr[32];
extern int total_pkt_captured;
#endif /* GLOBALS_H */