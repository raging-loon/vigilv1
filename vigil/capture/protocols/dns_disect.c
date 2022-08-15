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


#include "engine/rule/rule.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nethdr/dns.h"
#include "decode/dns_disect.h"
#include "utils.h"
#include "globals.h"
void dns_disect(const unsigned char * pkt, const struct rule_data * rdata){
  struct dns_pkt_data * dns_data = (struct dns_pkt_data*)(pkt);
  unsigned char * query = (unsigned char *)(pkt + sizeof(struct dns_pkt_data));
  if(dns_data->flags == 0){

    char * real_query = (char *)malloc(1024);
    memset(real_query,0,1024);
    get_dns_name(query,real_query);
    if(packet_print) printf("Query: %s\n",real_query);
    if(real_query) free(real_query);
  }
  
}



void get_dns_name(const unsigned char * qry, char * output){
  
  for(int i = 0; i < strlen((char *)qry); i++){
    
      if(qry[i] > 32) strncat(output,(char *)&qry[i],1);
      else strcat(output,".");
    
  }
}
