#include <stdio.h>
#include <stdlib.h>
#include "alerts.h"
#include "../../print_utils.h"


void stdout_alert(const struct rule_data** __rule_data, const struct rule ** __rule, int a_level){
  printf("TEST STDOUT ALERT\n");
}