#include "line_parser.h"
#include "rule.h"
#include "../actions/alerts.h"
#include "packet_parser.h"
#include "rule_parser.h"
#include "token.h"
#include "../../../globals.h"
#include "../../utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* alert stdout any TCP (name:"ioc-root-uid"; msg:"IOC Root UID returned"; type:str_match; target:"uid=0(root)";); */

void line_parser(const char * line){
  struct rule * rdata = &rules[++num_rules];
  rdata->port = NULL;
  rdata->protocol = NULL;
  int chars_parsed = 0;
  char * parser;
  char * content;
  bool data = false;
  while(chars_parsed != strlen(line)){
    parser = line + chars_parsed;
    if(strncmp(parser,))



  }
}