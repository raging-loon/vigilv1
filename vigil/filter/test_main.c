#include "parsing/rule_parser.h"
#include "parsing/rule.h"

struct rule * rules = 0;
int num_rules = 0;

int main(){
  rule_library_parser("../../npsi.conf");

}