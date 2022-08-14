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



struct fin_port_scan_ds{
  unsigned int fin_pkt_recv;
  unsigned long fin_pkt_times[30];
};  

struct basic_port_scan_ds{
  unsigned int rst_pkt_recv;
  unsigned long rst_pkt_times[30];
};

struct portscan_dataset{
  struct fin_port_scan_ds fin_data_set;
  struct basic_port_scan_ds basic_ps_ds;
};
#endif /* WL_DATA_SET_H */
