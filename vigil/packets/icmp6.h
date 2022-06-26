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
#ifndef ICMP6_H
#define ICMP6_H
#include <stdint.h>
struct __icmp6{
  uint8_t icmp_type;
  uint8_t icmp_code;
  uint16_t icmp_check_sum;
  uint32_t icmp_reserved;
  uint8_t icmp_src_lyr_type;
  uint8_t icmp_src_lyr_len;
  uint8_t addr[6];
};


#endif /* ICMP6_H */