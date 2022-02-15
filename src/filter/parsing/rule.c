#include "rule.h"
#include "../../../globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "../../engine/firewall/forward.h"
#include "dp_size.h"
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
      bool e_stat = r_engine(temp_rule,__rule_data);
      bool d_stat = d_engine(temp_rule, __rule_data);
      // if(d_stat && e_stat) printf("helo");
      bool r_stat = temp_rule->pkt_parser(__rule_data,temp_rule);
      printf("%s | %d | %d | %d\n",temp_rule->rulename ,e_stat,d_stat, r_stat);
      if(r_stat && (e_stat == true  && d_stat)){
        temp_rule->action(__rule_data,temp_rule,0);
        temp_rule->times_matched++;
      } else {
        if(NORAA_MODE == IPS_ACTIVE) forward_packet(__rule_data);
      }
    }
  }
}


bool r_engine(const struct rule * r, const struct rule_data * rdata){
  if(debug_mode) printf("in r_engine\n");
  if(rdata->__protocol == R_ICMP){
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
    if(r->tcp_data.ackset){
      if(ntohl(rdata->tcp_header->ack_seq) != r->tcp_data.ack) return false;
    }
    if(r->tcp_data.flagset){
      if(strcmp(rdata->tcp_flags, r->tcp_data.flags) != 0) return false;
      

    }
    if(r->tcp_data.seqset){
      if(rdata->tcp_header->seq != r->tcp_data.seq) return false;
    }
  } 
  if(rdata->ip_header != NULL){
    if(r->ip_data.ttlset){
      if(rdata->ip_header->ttl != r->ip_data.ttl) return false;
    }
  }
  return true;
}