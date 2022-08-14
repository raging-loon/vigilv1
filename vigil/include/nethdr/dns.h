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
#ifndef __DNS_H
#define __DNS_H
#include <stdint.h>


struct dns_pkt_data{
  uint16_t transaction_id;
  uint16_t flags;
  uint16_t questions;
  uint16_t ans_rr;
  uint16_t auth_rr;
  uint16_t additional_rr;
  
};
#endif /* __DNS_H */