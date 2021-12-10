#include "parsing/rule_parser.h"
#include "parsing/rule.h"

struct rules rule[32];

int main(){
  rule_library_parser("../../npsi.conf");

}