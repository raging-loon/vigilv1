/*!
 * @file globals.h
 * @author Conner Macolley
 * 
 * @section LICENSE
 * 
 *
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
 *
 *  @section DESCRIPTION
 *  Declare globals 
 */

#ifndef GLOBALS_H
#define GLOBALS_H
#include "src/statistics/ip_addr_stat.h"
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "src/engine/spi.h"
#include "src/filter/parsing/rule.h"
#include "src/statistics/arpcache.h"
#include "src/statistics/watchlist.h"
//    major.minor.patch
#define VERSION "1.0.0"
#define IDS_PASSIVE             1
#define IPS_ACTIVE              2    
#define MAX_RULES               1024        
// extern struct ip_addr_counter ip_stats[256];
// extern int ip_addr_stat_counter_len;

extern unsigned int total_pkt_captured;
//! @brief array of all of the rules
extern struct rule rules[MAX_RULES];
//! @brief counter for all of the rules
extern int num_rules;
//! @brief list of threads for thread management. 
extern pthread_t threads[64];
extern int thread_count;
//! @brief Determines whether the program is running in IDS or IPS mode
extern int npsi_mode;

//! @brief default is /etc/npsi/npsi.conf
extern char * default_config;
//! @brief default is /var/log/siglog.log
extern char * def_log_file;
//! @todo expand on this
extern char * default_host_conf;


extern bool debug_mode;
extern bool packet_print;
/*!
  @brief the blacklist
  @todo replace this with a struct that can hold different type of addresses
*/
extern struct blocked_ipv4 blocked_ipv4_addrs[32];
extern int blk_ipv4_len;
extern unsigned int pkt_counter;
extern struct watchlist_member watchlist[128];
extern int watchlist_num;


extern int strict_icmp_timestamp_req;
extern int strict_nmap_host_alive_check;

extern unsigned long last_clean_time;
extern unsigned long clean_delay;

extern int is_running;


extern struct arp_entry arpcache[255];
extern int arp_entries;

extern bool use_sqlite;
extern char sqlite_db_path[32];

extern unsigned int clean_delay_pkts;

extern bool quiet_exit;

// extern pthread_t threads[64];

extern int spi_max;
extern unsigned int total_conversations;

extern struct spi_members spi_table[1024];

extern char input_adapter[10];
extern char output_adapter[10];
extern int NPSI_MODE;
extern char local_ip[18];
extern char def_gw[18];

extern bool use_spi;
extern void add_thread(pthread_t *);

uint32_t homenet;
uint32_t homenetmask;


#endif /* GLOBALS_H */