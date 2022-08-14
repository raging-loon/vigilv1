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
#ifndef IGMP_V4_H
#define IGMP_V4_H
#include <stdint.h>

struct main_igmp{
  uint8_t type;
};

struct igmpv4_member_qry{
  uint8_t type;
  uint8_t max_resp_time;
  uint16_t checksum;
  uint32_t multicast_address;
  uint8_t flags;
  uint8_t QQIC;
  uint16_t num_src;
};

struct igmp_member_report{
  uint8_t type;
  uint8_t reserved;
  uint16_t checksum;
  uint16_t reserved2;
  uint16_t number_group_records;
  uint8_t record_type;
  uint8_t aux_data_len;
  uint16_t num_len;
  uint32_t multicast_address;
};
#endif /* IGMP_V4_H */