#include "rule.h"
#include "../../../globals.h"
#include <stdio.h>
#include "../../engine/firewall/forward.h"

/*
  *-*-*-*- rule.c -*-*-*-*
  @purpose Apply rules located in "rules" in /globals.h
  void rulemgr(const struct rule_data * __rule_data);
    ==> Apply the rules
    TODO: Add support for ports
*/
void rulemgr(const struct rule_data * __rule_data){
  for(int i = 0; i < num_rules + 1;){
    struct rule * temp_rule = &rules[i++];
    if(((temp_rule->protocol == R_ALL) || ( __rule_data->__protocol == temp_rule->protocol)) &&
      ((temp_rule->port == -1) || (__rule_data->src_port == temp_rule->port || __rule_data->dest_port == temp_rule->port))){

        
      if(temp_rule->pkt_parser(__rule_data,temp_rule) && r_engine(temp_rule,__rule_data)){
        temp_rule->action(__rule_data,temp_rule,0);
        temp_rule->times_matched++;
      } else {
        if(NPSI_MODE == IPS_ACTIVE) forward_packet(__rule_data);
      }
    }
  }
}


bool r_engine(const struct rule * r, const struct rule_data * rdata){
  if(rdata->__protocol == R_ICMP){
    if(r->icmp_data.code != -1){
      if(rdata->icmp_header->code != r->icmp_data.code) return false;
    }
    if(r->icmp_data.id != -1){
      if(rdata->icmp_header->id != r->icmp_data.id) return false;
    }
    if(r->icmp_data.seq != -1){
      if(rdata->icmp_header->seq != r->icmp_data.seq) return false;
    }
    if(r->icmp_data.type != -1){
      if(rdata->icmp_header->type != r->icmp_data.type) return false;
    }
  } 
  else if(rdata->__protocol == R_TCP){
      printf("hello");
    if(r->tcp_data.ack != -1){
      if(rdata->tcp_header->ack != r->tcp_data.ack) return false;
    }
    if(r->tcp_data.flags != -1){
      if(strcmp(rdata->tcp_flags, r->tcp_data.flags) != 0) return false;
    }
    if(r->tcp_data.seq != -1){
      if(rdata->tcp_header->seq != r->tcp_data.seq) return false;
    }
  } else if(rdata->ip_header != NULL){
    if(r->ip_data.ttl != -1){
      if(rdata->ip_header->ttl != r->ip_data.ttl) return false;
    }
  }
  return true;
}