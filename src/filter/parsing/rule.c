#include "rule.h"
#include "../../../globals.h"
#include <stdio.h>
void rulemgr(const struct rule_data * __rule_data){
  printf("rulemgr\n");
  for(int i = 0; i < num_rules; i++){
    if(rules[num_rules].pkt_parser(__rule_data,(const struct rule *)&rules[num_rules])){
      rules[num_rules].action(__rule_data,(const struct rule *)&rules[num_rules],0);
    }
  }
}