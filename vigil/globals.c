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
#include "globals.h"
#include "statistics/arpcache.h"
#include "engine/spi.h"
#include "filter/parsing/rule.h"
#include <pthread.h>
#include <stdlib.h>
// globals defined in @globals.h
// config options

struct rule * rules = {0};

unsigned int global_alert_method;
unsigned int pkt_counter;
unsigned int clean_delay_pkts = 0;
unsigned int total_pkt_captured = 0;

uint32_t homenet;
uint32_t homenetmask;

unsigned long last_clean_time;
unsigned long clean_delay;

int thread_count = 0;
int strict_icmp_timestamp_req;
int strict_nmap_host_alive_check;
int blk_ipv4_len = -1;
int num_rules = -1;
int arp_entries = -1;
int spi_max = 200;
int vigil_location;
int VIGIL_MODE = 0xffff;
int global_rule_action;

pid_t ipc_router_pid;
bool demo_mode;
bool quiet_exit = false;
bool use_sqlite;
bool packet_print;
bool in_test_mode;
bool debug_mode;
bool use_spi;


pthread_t threads[64];
// info objects
struct blocked_ipv4 blocked_ipv4_addrs[32];
struct arp_entry arpcache[255];


char ip_addr[32];
char input_adapter[10];
char output_adapter[10];
char local_ip[18];
char def_gw[18];
char sqlite_db_path[32];

// default files
char * default_config = "/etc/vigil/vigil.conf";
char * def_log_file = "/var/log/vigil/siglog.log";
char * default_host_conf = "/etc/vigil/hosts.conf";





void add_thread(pthread_t * pthrd){
  threads[thread_count++] = *pthrd;
}

void init_globals(){
  rules = (struct rule *)malloc(sizeof(struct rule) * MAX_RULES);
}

void free_globals(){
  free_rules(); // frees prange if applicable
  free(rules);
}