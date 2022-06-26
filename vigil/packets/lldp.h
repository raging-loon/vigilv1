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
#ifndef __LLDP_H
#define __LLDP_H
#include <stdint.h>
struct chassis_subtype{
  uint16_t tlv_info;
  uint16_t chassis_id_subtype
  uint8_t chassis_id[6];
};



struct lldp_type_1{
  struct chassis_subtype chassis_info;
  
};




#endif __LLDP_H