/*
 * Copyright 2021 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/statistics/ip_addr_stat.h"
#include <stdint.h>
#include <stdbool.h>
#include "src/filter/parsing/rule.h"
#include "src/statistics/arpcache.h"
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


extern int strict_icmp_timestamp_req;
extern int strict_nmap_host_alive_check;

extern unsigned long last_clean_time;
extern unsigned long clean_delay;

extern int is_running;


extern struct arp_entry arpcache[255];
extern int arp_entries;

extern bool use_mysql;
extern char * mysql_user;
extern char * mysql_password;

#endif /* GLOBALS_H */