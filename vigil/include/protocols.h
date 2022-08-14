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
#ifndef PROTOCOLS_H
#define PROTOCOLS_H
#include <netinet/ether.h>
#include <netinet/ip.h>
#define L2_ARP        1544
#define L2_RARP       0x3580
#define L3_IPV6       0xdd86
#define L3_IPV4       8

#define ETH_HDR_SZ     sizeof(struct ethhdr)
#define IPv4_HDR_LN    sizeof(struct iphdr)
typedef enum {
  RAW_ETHERNET = 90,
  RAW_IPv4,
  TCP,
  UDP,
  ICMP,
} traffic_class;

#endif /* PROTOCOLS_H */