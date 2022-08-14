/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/
#ifndef GLOBALS_H
#define GLOBALS_H
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "engine/spi.h"
#include "config/rule.h"
#include "statistics/arpcache.h"
//    major.minor.patch
#define VERSION "1.0.0"
#define PROG_NAME "/bin/vigil"
#define VERSION_NUM 0x010000
#define IDS_PASSIVE             1
#define IPS_ACTIVE              2    
#define MAX_RULES               160   
#define INTERNAL                3
#define EXTERNAL                4
void init_globals();
void free_globals();


extern unsigned int total_pkt_captured;
//! @brief array of all of the rules
extern struct rule * rules;
//! @brief counter for all of the rules
extern int num_rules;
//! @brief list of threads for thread management. 
extern pthread_t threads[64];
extern int thread_count;
//! @brief Determines whether the program is running in IDS or IPS mode
extern int vigil_mode;
extern bool demo_mode;
//! @brief default is /etc/npsi/npsi.conf
extern char * default_config;
//! @brief default is /var/log/siglog.log
extern char * def_log_file;
//! @todo expand on this
extern char * default_host_conf;

extern int vigil_location;
extern bool debug_mode;
extern bool packet_print;
/*!
  @brief the blacklist
  @todo replace this with a struct that can hold different type of addresses
*/
extern struct blocked_ipv4 blocked_ipv4_addrs[32];
extern int blk_ipv4_len;
extern unsigned int pkt_counter;


extern int strict_icmp_timestamp_req;
extern int strict_nmap_host_alive_check;

extern unsigned long last_clean_time;
extern unsigned long clean_delay;

extern int global_rule_action;

extern struct arp_entry arpcache[255];
extern int arp_entries;

extern bool use_sqlite;
extern char sqlite_db_path[32];

extern unsigned int clean_delay_pkts;

extern bool quiet_exit;

// extern pthread_t threads[64];

extern int spi_max;


extern char input_adapter[10];
extern char output_adapter[10];
extern int VIGIL_MODE;
extern char local_ip[18];
extern char def_gw[18];

extern bool use_spi;
extern void add_thread(pthread_t *);

//! @brief homenet address for anding
extern uint32_t homenet;
//! @brief homenet netmask for anding
extern uint32_t homenetmask;

extern bool in_test_mode;
extern unsigned int global_alert_method;

extern pid_t ipc_router_pid;

#endif /* GLOBALS_H */