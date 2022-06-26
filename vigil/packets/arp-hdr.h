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
#ifndef ARP_HDR
#define ARP_HDR
#include <stdint.h>
struct arp_hdr{
  // unsigned int hw_type:             16;
  // unsigned int proto_type:          16;
  // unsigned int hwlen:               8;
  // unsigned int protoln:             8;
  // unsigned int opcode:              16;
  // unsigned char src_mac[6];
  // unsigned char src_ip[4];
  // unsigned char dst_mac[6];
  // unsigned char dst_ip[4];
  // unsigned char runoff[4];
  uint16_t      hw_type;
  uint16_t      proto_type;
  uint8_t       hw_len;
  uint8_t       protoln;
  uint16_t      opcode;
  uint8_t       src_mac[6];
  uint8_t      src_ip[4];
  uint8_t       dst_mac[6];
  uint8_t      dst_ip[4];
};

#endif /* ARP_HDR */