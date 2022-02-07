#include "rule.h"
#include "../../../globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../engine/firewall/forward.h"

/*
  *-*-*-*- rule.c -*-*-*-*
  @purpose Apply rules located in "rules" in /globals.h
  void rulemgr(const struct rule_data * __rule_data);
    ==> Apply the rules
    TODO: Add support for ports
*/
void rulemgr(const struct rule_data * __rule_data){
  // printf("In rulemgr\n");
  for(int i = 0; i < num_rules + 1;){
    struct rule * temp_rule = &rules[i++];
    if(((temp_rule->protocol == R_ALL) || ( __rule_data->__protocol == temp_rule->protocol)) &&
      ((temp_rule->port == -1) || (__rule_data->src_port == temp_rule->port || __rule_data->dest_port == temp_rule->port))){
        if(debug_mode) printf("rulemgr: %s\n",temp_rule->rulename);
      bool e_stat = r_engine(temp_rule,__rule_data);
      if(temp_rule->pkt_parser(__rule_data,temp_rule) && e_stat){
        temp_rule->action(__rule_data,temp_rule,0);
        temp_rule->times_matched++;
      } else {
        if(NPSI_MODE == IPS_ACTIVE) forward_packet(__rule_data);
      }
    }
  }
}


bool r_engine(const struct rule * r, const struct rule_data * rdata){
  if(debug_mode) printf("in r_engine\n");
  if(rdata->__protocol == R_ICMP){
    if(debug_mode) printf("ICMP\n");
    if(r->icmp_data.codeset){
      if(rdata->icmp_header->code != r->icmp_data.code) return false;
    }
    if(r->icmp_data.idset){
      if(rdata->icmp_header->id != r->icmp_data.id) return false;
    }
    if(r->icmp_data.seqset){
      if(rdata->icmp_header->seq != r->icmp_data.seq) return false;
    }
    if(r->icmp_data.typeset){
      if(rdata->icmp_header->type != r->icmp_data.type) return false;
    }
  } 
  else if(rdata->__protocol == R_TCP){
    if(r->tcp_data.ack != NULL){
      if(rdata->tcp_header->ack != r->tcp_data.ack) return false;
    }
    if(r->tcp_data.flags != NULL){
      if(strcmp(rdata->tcp_flags, r->tcp_data.flags) != 0) return false;
    }
    if(r->tcp_data.seq != NULL){
      if(rdata->tcp_header->seq != r->tcp_data.seq) return false;
    }
  } else if(rdata->ip_header != NULL){
    if(r->ip_data.ttl != NULL){
      if(rdata->ip_header->ttl != r->ip_data.ttl) return false;
    }
  }
  return true;
}