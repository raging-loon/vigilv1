#include "rule.h"
#include "../../../globals.h"
#include <stdio.h>
void rulemgr(const struct rule_data * __rule_data){
  // printf("rulemgr\n");
  for(int i = 0; i < num_rules + 1;){
    struct rule * temp_rule = &rules[i++];
    // printf("Testing %s\n",temp_rule->rulename);
    if(temp_rule->pkt_parser(__rule_data,temp_rule)){
      temp_rule->action(__rule_data,temp_rule,0);
      temp_rule->times_matched++;
    }
  }
}