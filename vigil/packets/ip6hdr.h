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
#ifndef IP6_HDR_H
#define IP6_HDR_H
#include <stdint.h>
struct ip6hdr{
  unsigned int version:             4;
  unsigned int t_class:             8;
  unsigned int flow_label:          20;
  unsigned int payload_len:         16;
  unsigned int n_hdr:               8;
  unsigned int hop_limit:           8;
  uint8_t srcaddr[16];
  
  uint8_t dstaddr[16];            
};

#endif /* IP6_HDR_H */