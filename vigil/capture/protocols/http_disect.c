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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "engine/rule/rule.h"



void http_disect(const unsigned char * pkt, const struct rule_data * rdata){
  // printf("%s\n",pkt);
  // int loc = strloc((const char *)pkt,0x0d);
  // printf("Strloc successful\n");
  // if(!test_string_arr_print((const char *)pkt)) return;
  // char request_hdr[1024];
  // strncpy(request_hdr,(const char *)pkt,loc );

  // printf("%s\n",request_hdr);
  
}

