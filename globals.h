#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/statistics/ip_addr_stat.h"
#include <stdint.h>
#include <stdbool.h>
#include "src/filter/parsing/rule.h"
#include "src/statistics/watchlist.h"
//    major.minor.patch
#define VERSION "1.0.0"
extern struct ip_addr_counter ip_stats[256];
extern int ip_addr_stat_counter_len;

extern char ip_addr[32];

extern int total_pkt_captured;

extern struct rule rules[128];
extern int num_rules;

extern int npsi_mode;

extern char * default_config;
extern char * def_log_file;
extern char * default_host_conf;

extern bool debug_mode;
extern struct blocked_ipv4 blocked_ipv4_addrs[32];
extern int blk_ipv4_len;

extern struct watchlist_member watchlist[128];
extern int watchlist_num;

#endif /* GLOBALS_H */