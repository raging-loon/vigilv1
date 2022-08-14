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

#include "engine/rule/alerts.h"
#include "engine/rule/packet_parser.h"
#include "engine/rule/rule.h"
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include <regex.h>

/*
  *-*-*-*- packet_parser.c -*-*-*-*
  @purpose Provides parsing for packets so rules can be applied.
  bool str_match_parser(const struct rule_data * rdata, const struct rule * __rule);
    ==> Convert both the entire packet and __rule->target_chars into hexadecimal characters.
        __rule->target_chars is searched for within the hexadecimal representation of the packet
  
  @TODO: add a function for raw bit matching and rename bit_match_parser.  
*/

bool str_match_parser(const struct rule_data * rdata, const struct rule * __rule){
  if(rdata->pkt_len <= 0) return false;  
  // printf("%d\n",rdata->pkt_len);
  char temp_pkt[ (rdata->pkt_len * 2) + 2];

  memset(&temp_pkt, 0, sizeof(temp_pkt));
  int chars_filled = 0; // we have to use this because offset could be and odd number
  if(__rule->depth != 0){
    
    for(int i = __rule->offset; i < __rule->depth; i++){
      sprintf(temp_pkt + chars_filled++ * 2, "%02x",rdata->pkt[i]);
    }
  } else {
    for(int i = __rule->offset; i < rdata->pkt_len; i++){
      
      sprintf(temp_pkt + chars_filled++ * 2, "%02x",rdata->pkt[i]);
    }
  }
  
  if(strstr(temp_pkt,__rule->rule_target) != NULL)
    return true;
 
  
  
  return false;

}

bool is_blocked_ipv4(const char * ipv4_addr){
  for(int i = 0; i < blk_ipv4_len + 1; i++){
    // printf("Testing %s and %s\n",ipv4_addr,blocked_ipv4_addrs[blk_ipv4_len].ipv4_addr);
    if(strcmp(ipv4_addr,blocked_ipv4_addrs[i].ipv4_addr) == 0)
      return true;
    
  }
  return false;
}


bool none(const struct rule_data * rdata, const struct rule * __rule){
  return true;
}


bool pcre_match(const struct rule_data * rdata, const struct rule *r){
  // regex_t rgx;

  // regcomp(&rgx,(const char *)&r->pcretarget,0);
  
  if(regexec(&r->pcre,(char *)rdata->pkt,0,NULL,0) == REG_NOMATCH) return false;
  else return true;
  
  
}