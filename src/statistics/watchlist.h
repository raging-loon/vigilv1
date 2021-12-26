#ifndef WATCHLIST_H
#define WATCHLIST_H
#include <stdbool.h>
#include <stdint.h>
// max time between RST packets 7442974


struct watchlist_member{
  const char * ip_addr;
  int rst_pkt_recv;
  int suspect_activity;
  unsigned long last_rst_pkt_times[20];
  union{
    unsigned long start_time;
    int num_done;
    int icmp_echo_sent;
    int tcp_syn_sent;
    int tcp_ack_sent;
    int icmp_time_req_sent;
    unsigned long end_time;
  } nmap_watch_host_alive_watch;


}; 

/*
struct nmap_host_alive_watch{
  unsigned long start_time;
  int icmp_echo_sent;
  int tcp_syn_sent;
  int tcp_ack_sent;
  int icmp_time_req_sent;
};
*/
bool tcp_portscan_detect(const struct watchlist_member * );

void member_ready_for_scan();


int member_exists(const char *);
#endif /* WATCHLIST_H */
