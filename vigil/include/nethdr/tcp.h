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
#ifndef __TCP_H_
#define __TCP_H_
#include <stdint.h>
#include <bits/endian.h>
struct __tcp{
  uint16_t source;
  uint16_t dest;
  uint32_t seq;
  uint32_t ack_seq;
#if __BYTE_ORDER == __LITTLE_ENDIAN
  uint16_t  res1: 4;
  uint16_t  doff: 4;
  uint16_t  fin:  1;
  uint16_t  syn:  1;
  uint16_t  rst:  1;
  uint16_t  psh:  1;
  uint16_t  ack:  1;
  uint16_t  urg:  1;
  uint16_t  ece:  1;
  uint16_t  cwr:  1;
           
#elif defined(__BIG_ENDIAN__)
  uint16_t doff: 4;
  uint16_t res1: 4;
  uint16_t cwr:  1;
  uint16_t ece:  1;
  uint16_t urg:  1;
  uint16_t ack:  1;
  uint16_t psh:  1;
  uint16_t rst:  1;
  uint16_t syn:  1;
  uint16_t fin:  1;
#else
#   error "Fix <bits/endian.h>"
#endif
  uint16_t window;
  uint16_t check;
  uint16_t urg_ptr;
} __attribute__((packed));
#endif /* __TCP_H_ */