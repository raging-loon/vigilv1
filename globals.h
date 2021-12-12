#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/statistics/ip_addr_stat.h"
#include <stdint.h>
#include <stdbool.h>
#include "src/filter/parsing/rule.h"
extern struct ip_addr_counter ip_stats[256];
extern int ip_addr_stat_counter_len;
extern char ip_addr[32];
extern int total_pkt_captured;
extern struct rule *rules;
extern int num_rules;
extern int npsi_mode;


#endif /* GLOBALS_H */