#include "rule.h"
#include "../../../globals.h"
#include <stdio.h>
#include "../../utils.h"
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
static void rule_app(struct rule * r, const struct rule_data * rdata){
  bool e_stat = r_engine(r,rdata);    
  bool d_stat = d_engine(r, rdata);
  bool r_stat = r->pkt_parser(rdata,r);
  // printf("%s | %d | %d | %d\n",temp_rule->rulename ,e_stat,d_stat, r_stat)
  if(r_stat && (e_stat == true  && d_stat)){
    r->action(rdata,r,0);
    r->times_matched++;
  } else {
    if(NORAA_MODE == IPS_ACTIVE) forward_packet(rdata);
  }
}
void rulemgr(const struct rule_data * __rule_data){
  // printf("In rulemgr\n");
  for(int i = 0; i < num_rules + 1;){
    struct rule * temp_rule = &rules[i++];
    if(in_test_mode){
      if(temp_rule->flow == FLOW_INWARD) temp_rule->flow = FLOW_OUTWARD;
      else if(temp_rule->flow == FLOW_OUTWARD) temp_rule->flow = FLOW_INWARD; 
    }
    if(((temp_rule->protocol == R_ALL) || ( __rule_data->__protocol == temp_rule->protocol))){
      if(demo_mode) rule_app(temp_rule,__rule_data);

      else if((temp_rule->flow == FLOW_EITHER || __rule_data->flow == temp_rule->flow)){
        // printf("%s: %d|%d <-----> %d|%d hellos\n",temp_rule->rulename,temp_rule->src_port,temp_rule->dest_port,__rule_data->src_port,__rule_data->dest_port);
        if(temp_rule->protocol == R_ICMP)
          rule_app(temp_rule,__rule_data);
        else {
          if(temp_rule->flow == FLOW_EITHER){
            if((temp_rule->src_port == R_ALL || IS_PORT_DEST_SRC(__rule_data->src_port,__rule_data->dest_port,temp_rule->src_port)) &&
              (temp_rule->dest_port == R_ALL || IS_PORT_DEST_SRC(__rule_data->src_port,__rule_data->dest_port,temp_rule->dest_port))){
                rule_app(temp_rule,__rule_data);
              }

          }
          else if((temp_rule->src_port == R_ALL || (temp_rule->src_port == __rule_data->src_port)) &&
                  (temp_rule->dest_port == R_ALL || (temp_rule->dest_port == __rule_data->dest_port)))
            rule_app(temp_rule,__rule_data);

        }
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
      // printf("%ld | %d\n", ntohl(rdata->tcp_header->ack_seq), ntohl(r->tcp_data.ack));
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