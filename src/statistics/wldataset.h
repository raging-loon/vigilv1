#ifndef WL_DATA_SET_H
#define WL_DATA_SET_H

struct nmap_watch_host_alive{
  unsigned long start_time;
  int icmp_echo_sent;
  int tcp_syn_sent;
  int tcp_ack_sent;
  int icmp_time_req_sent;
  int num_done;
  unsigned long end_time;
};

struct ftp_sec_data{
  unsigned int ftp_connect_times[10];
  int twh_prog;
  unsigned int first_failed_login_attempt_time;
  int failed_login_attempts;
  // full three_way_handshake on ftp port
};


struct brute_force_ds{
  struct ftp_sec_data wl_ftp_sec_data;
};

#endif /* WL_DATA_SET_H */
