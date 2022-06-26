/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Foobar. 
    If not, see <https://www.gnu.org/licenses/>. 

*/


#include "homenet.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t homenet_toi(const char * ip_addr){
  char num_str[9] = {0};
  
  char * octet = strtok(ip_addr,".");
  while(octet != NULL){
    sprintf(num_str + strlen(num_str),"%02x",atoi(octet));
    octet = strtok(NULL,".");
  }
  return (uint32_t)strtol(num_str,NULL,16);
}
