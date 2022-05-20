/*
 * Copyright 2021-2022 Conner Macolley
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
#include "globals.h"
// #include "src/statistics/watchlist.h"
#include "src/statistics/arpcache.h"
#include "src/engine/spi.h"
#include "src/filter/parsing/rule.h"
#include <pthread.h>
// globals defined in @globals.h
// config options
bool demo_mode;
int strict_icmp_timestamp_req;
int strict_nmap_host_alive_check;
pthread_t threads[64];
int thread_count = 0;
unsigned int total_pkt_captured = 0;
int blk_ipv4_len = -1;
int num_rules = -1;
// int watchlist_num = -1;
int arp_entries = -1;
int is_running;
int spi_max = 200;
unsigned long last_clean_time;
unsigned long clean_delay;
unsigned int pkt_counter;
// info objects
struct rule rules[MAX_RULES] = {0};// = (struct rule *)malloc(sizeof(struct rule) * 128);
struct blocked_ipv4 blocked_ipv4_addrs[32];
// struct watchlist_member watchlist[128] = {0};
struct arp_entry arpcache[255];
char ip_addr[32];
bool debug_mode;
// default files
char * default_config = "/etc/vigil/vigil.conf";
char * def_log_file = "/var/log/vigil/siglog.log";
char * default_host_conf = "/etc/vigil/hosts.conf";

bool use_sqlite;
char sqlite_db_path[32];

unsigned int clean_delay_pkts = 0;
bool packet_print;
bool quiet_exit = false;



int vigil_location;

int VIGIL_MODE = 0xffff;
char input_adapter[10];
char output_adapter[10];
char local_ip[18];
char def_gw[18];
bool use_spi;

uint32_t homenet;
uint32_t homenetmask;
bool in_test_mode;
void add_thread(pthread_t * pthrd){
  threads[thread_count++] = *pthrd;
}