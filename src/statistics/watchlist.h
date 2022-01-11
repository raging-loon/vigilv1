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


#ifndef WATCHLIST_H
#define WATCHLIST_H
#include <stdbool.h>
#include "wldataset.h"
#include <stdint.h>
// max time between RST packets 7442974



struct watchlist_member{
  unsigned long last_time_seen;
  char ip_addr[32];
  int suspect_activity;
  struct nmap_watch_host_alive nmap_watch_host_alive_watch;
  struct portscan_dataset psds;
  int failed_ftp_login_attempts;
  int frag_ipv4_sent;




  unsigned int count;
  unsigned int tcp_sent;
  unsigned int udp_sent;
  unsigned int icmp_sent;
  unsigned int tcp_recv;
  unsigned int udp_recv;
  unsigned int icmp_recv;
  unsigned int unknown_sent;
  unsigned int unknown_recv;
  unsigned int total_recv;
  unsigned int total_sent;
  unsigned int sz_recv;
  unsigned int sz_sent;
  unsigned int total_sz;
  
}; 



bool tcp_rst_portscan_detect(const struct watchlist_member * );
bool fin_rst_portscan_detect(const struct watchlist_member *);
void member_ready_for_scan();


int member_exists(const char *);

void init_member(const char *);



#endif /* WATCHLIST_H */
