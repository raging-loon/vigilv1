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
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "engine/rule/rule_init.h"

void rule_processor(){

  for(int i = 0; i < num_rules + 1; i++){

    process_rule(&rules[i]);
  }
}

void process_rule(struct rule * r){
  if(!r->uses_pcre){
    char target[(strlen(r->rule_target) * 2) + 2];
    unsigned int parsing_byte = 0;
    strcpy(r->raw_target, r->rule_target);
    for(int i = 0; i < strlen(r->rule_target); i++){
      if(r->rule_target[i] == '|'){
        if(parsing_byte != 0) parsing_byte = 0;
        else parsing_byte = 1;
        continue;
      }
      if(parsing_byte == 1){
        sprintf(target + i -1, "%c", r->rule_target[i]);
      } else {
        sprintf(target + i * 2,"%02x",r->rule_target[i]);
      }
    }

    memset(&r->rule_target,0,sizeof(r->rule_target));
    strcpy(r->rule_target,target);
  }

}