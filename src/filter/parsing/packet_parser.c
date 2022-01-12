#include "../actions/alerts.h"
#include "packet_parser.h"
#include "rule.h"
#include <stdio.h>
#include <string.h>
#include "../../../globals.h"

/*
  *-*-*-*- packet_parser.c -*-*-*-*
  @purpose Provides parsing for packets so rules can be applied.
  bool bit_match_parser(const struct rule_data * __rule_data, const struct rule * __rule);
    ==> Convert both the entire packet and __rule->target_chars into hexadecimal characters.
        __rule->target_chars is searched for within the hexadecimal representation of the packet
  
  @TODO: add a function for raw bit matching and rename bit_match_parser.  
*/

bool bit_match_parser(const struct rule_data * __rule_data, const struct rule * __rule){

  char temp_pkt[ __rule_data->pkt_len * 2];
  char temp_target[strlen(__rule->rule_target) * 2];
  for(int i = 0; i < __rule_data->pkt_len; i++){
    sprintf(temp_pkt + i * 2, "%02x",__rule_data->pkt[i]);
  }
  for(int i = 0; i < strlen(__rule->rule_target); i++){
    sprintf(temp_target +i * 2, "%02x",__rule->rule_target[i]);
  }
  if(strstr(temp_pkt,temp_target) != NULL) return true;
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