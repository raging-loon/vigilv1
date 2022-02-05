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
static char * substr(char * str, int left, int right){
  char sub = (char *)malloc(sizeof(char) * (right - left + 2));
  for(int i = left; i <= right; i++){
    sub[i - left] = str[i];
  }
  sub[right - left + 1] = '\0';
  return sub;
}
static bool delimit(char c){
  return c == ' ';
}

void line_parser(const char * line){
  struct rule * rdata = &rules[++num_rules];
  rdata->port = -1;
  rdata->protocol = -1;
  int chars_parsed = 0;
  char * parser;
  char * content;
  bool data = false;
  int left = 0, right = 0;
  int len = strlen(line);
  bool parsing_msg_str = false;
  while(right <= len && left <= right){
    if(!delimit(line[right])) right++;

    if(delimit(line[right]) && right == left){
      if(line[right] == ':'){
        printf("Found operator");
      }
      right++;
      left = right;
    
    
    } else if(delimit(line[right]) && left != right || (right == len && left != right)){
      char * sub = substr(line, left, right -1);

    }

  }
}


static bool isdigit(const char * pos_num){
  for(int i = 0; i < strlen(pos_num); i++){
    if(pos_num[i] != '0' && pos_num[i] != '1' && pos_num[i] != '2' &&
       pos_num[i] != '3' && pos_num[i] != '4' && pos_num[i] != '4' &&
       pos_num[i] != '5' && pos_num[i] != '6' && pos_num[i] != '7' &&
       pos_num[i] != '8' && pos_num[i] != '9') 
      return false;
  }
  return true;
}


static void assign_port_number(const char * sub, struct rule * r){
  if(isdigit(sub))
    r->port = atoi(sub);
  else if(strcmp(sub,"any") == 0)
    r->port = -1;
  
}

static void assign_protocol(const char * sub, struct rule * r){
  if(strcmp(sub,"ANY") == 0)
    r->protocol = R_ALL;
  else if(strcmp(sub,"ICMP") == 0)
    r->protocol = R_ICMP;
  else if(strcmp(sub,"TCP") == 0)
    r->protocol = R_TCP;
  else if(strcmp(sub,"UDP") == 0)
    r->protocol = R_UDP;
}