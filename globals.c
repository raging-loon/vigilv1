#include "globals.h"
#include "src/statistics/watchlist.h"
#include "src/statistics/arpcache.h"
#include "src/statistics/spi.h"
#include "src/filter/parsing/rule.h"
#include <pthread.h>
// globals defined in @globals.h
// config options
int strict_icmp_timestamp_req;
int strict_nmap_host_alive_check;
pthread_t threads[64];
// counters
unsigned int total_pkt_captured = 0;
int blk_ipv4_len = -1;
int num_rules = -1;
int watchlist_num = -1;
int arp_entries = -1;
int is_running;
unsigned long last_clean_time;
unsigned long clean_delay;
unsigned int pkt_counter;
// info objects
struct rule rules[128] = {0};// = (struct rule *)malloc(sizeof(struct rule) * 128);
struct blocked_ipv4 blocked_ipv4_addrs[32];
struct watchlist_member watchlist[128] = {0};
struct arp_entry arpcache[255];
char ip_addr[32];
bool debug_mode;
// default files
char * default_config = "/etc/npsi/npsi.conf";
char * def_log_file = "/var/log/npsi/siglog.log";
char * default_host_conf = "/etc/npsi/hosts.conf";

bool use_sqlite;
char sqlite_db_path[32];

unsigned int clean_delay_pkts = 0;
bool packet_print;
bool quiet_exit = false;