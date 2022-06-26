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
#ifndef DHCP_4_H
#define DHCP_4_H
#include <stdint.h>


struct dhcpv4{
  uint8_t message_type;
  uint8_t hw_type;
  uint8_t hw_addr_len;
  uint8_t hops;
  uint32_t transaction_id;
  uint16_t sec_elapsed;
  uint16_t bootp_flags;
  uint8_t client_ip_addr[4];
  uint8_t a_client_ip_addr[4];
  uint8_t nxt_server_ip_addr[4];
  uint8_t relay_agent_ip_addr[4];
  uint8_t client_mac[6];
  uint8_t cleint_hw_addr_pad[10];
  uint8_t server_host_name[64];
  uint8_t boot_file_name[128];
  uint32_t magic_cookie;
  // this defines the message type
  uint8_t dhcp_msg_type[3];
  // msg_type[0] = actual type
  // msg_type[1] = length
  // msg_type[2] = options
  uint8_t server_id[6];
  uint8_t lease_time[6];
  
};


#endif /* DHCP_4_H */