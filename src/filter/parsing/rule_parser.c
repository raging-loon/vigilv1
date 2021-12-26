#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rule_parser.h"
#include "rule.h"
#include "packet_parser.h"
#include "../actions/alerts.h"
#include "../../../globals.h"
static bool is_rule(const char *);
static bool is_comment(const char * line);
static void rstrip(char * );
static void syntax_error(const char * line, int line_no);
static void get_ruletype(const char * , struct rule *);
static void get_action(const char * , struct rule *);

// also the main config parser
void rule_library_parser(const char * alt_file){
  // alt_file will be determined elsewhere
  FILE * fp = fopen(alt_file,"r");
  if(fp == NULL){
    printf("Error opening configuration file: %s\n",alt_file);
    exit(EXIT_FAILURE);
  }
  size_t pos;
  size_t len = 0;
  char * line = NULL;
  
  while((pos = getline(&line,&len,fp)) != -1){
    line[strcspn(line,"\n")] = 0;
    if(is_comment(line) == true) continue;
    else if(strncmp(line,"strict_icmp_timestamp_req=",26) == 0){
      if(strcmp(line + 27,"YES") == 0) strict_icmp_timestamp_req = true;
      else strict_icmp_timestamp_req = false;
    }
    else if(strncmp(line,"strict_nmap_host_alive_check=",29) == 0){
      if(strcmp(line + 29, "YES") == 0) strict_nmap_host_alive_check = true;
      else strict_nmap_host_alive_check = false;
    }
    else if(is_rule(line)){
      // printf("Parsing: %s\n",line);
      rule_parser(line);
    } 
  }
}
static bool is_rule(const char * line){
  return line[0] == '$' ? true : false;
}

static bool is_comment(const char * line){
  return strstr(line,"#") != NULL ? true : false;
}

static void rstrip(char * line){
  line[strcspn(line,"\n")] = 0;
}

static void syntax_error(const char * line, int line_no){
  printf("Syntax error at line %d: %s\n",line_no,line);
  exit(EXIT_FAILURE);
}

void rule_parser(const char * __filename){
  // + 1 for the $ at the beggining
  // also for the " " at the beggining when filename is given over network
  const char * filename = __filename + 1;
  num_rules = num_rules + 1;
  struct rule *  __rule = &rules[num_rules];
  __rule->times_matched = 0;
  FILE * fp = fopen(filename,"r");
  if(fp == NULL){
    printf("Error opening rule file: %s. Refusing to continue\n",filename);

    exit(EXIT_FAILURE);
  }
  printf("Parsing file %s\n",filename);
  bool parsing_rule = false;
  size_t pos;
  size_t len = 0;
  char * line = NULL;
  int lines = 0;
  while((pos = getline(&line,&len,fp)) != -1){
    lines++;
    if(is_comment(line))
      continue;
    rstrip(line);

    if(strcmp("\x00",line) == 0) continue;
    
    if(strstr(line,"RULE_START{")){
      parsing_rule = true;
    }
    
    else if(strstr(line,"name=\"") != NULL){
      if(!parsing_rule) syntax_error(line,lines);
      // maybe add more flexibility with tabbing and stuff
      char name[strlen(line + 8) + 2];// = line + 8;
      strcpy(name,line+8);
      name[strcspn(name,"\"")] = 0;
      strcpy((char *)&__rule->rulename,(char *)&name);
      
    }

    else if(strstr(line,"type=") != NULL){
      if(!parsing_rule) syntax_error(line,lines);
      char * ruletype = line + 7;
      // printf("%s\n",ruletype);
      get_ruletype(ruletype,__rule);
      
    }
    
    else if(strstr(line,"action=") != NULL){
      if(!parsing_rule) syntax_error(line,lines);
      char * action = line + 9;
      get_action(action,__rule);
    }
    
    else if(strstr(line,"target_contents=") != NULL){
      if(!parsing_rule) syntax_error(line,lines);
      char * contents = line + 19;
      strcpy(__rule->rule_target,contents);
    }
    
    else if(strstr(line,"}") != NULL){
      parsing_rule = false;
    }
    else{
      syntax_error(line,lines);
    }

  }
  if(parsing_rule){
    printf("Please end your rule with a closing } on a newline\n");
    exit(EXIT_FAILURE);
  }
}



static void get_ruletype(const char * __line, struct rule * __rule){
  if(strcmp(__line,"bit_match") == 0){
    __rule->pkt_parser = bit_match_parser;
    return;
  }

  else {
    printf("Unknown rule type: %s\n",__line);
    exit(EXIT_FAILURE);
  }
  
}


static void get_action(const char * __line, struct rule * __rule){
  if(strcmp(__line,"stdout_alert") == 0){
    __rule->action = stdout_alert; 
    return;
  } 
  else {
    printf("Unknown action: %s\n",__line);
    exit(EXIT_FAILURE);
  }

}


void deny_conf_parser(char * file){
  FILE * fp = fopen(file,"r");
  if(fp == NULL){
    printf("Error opening %s for expl/implicit deny parsing\n",file);
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t pos, len = 0;
  while((pos = getline(&line,&len,fp)) != -1){
    rstrip(line);
    if(is_comment(line)) continue;
    
    if(strcmp("\x00",line) == 0) continue;
    if(strstr(line,"ipv4")){
      struct blocked_ipv4 * temp = &blocked_ipv4_addrs[++blk_ipv4_len];
      char * ipv4_addr = line + 5;
      // printf("%s\n",ipv4_addr);
      strcpy(temp->ipv4_addr ,ipv4_addr);
    } 
  }
  
  if(line) free(line);
  
  /*
  for(int i = 0; i < blk_ipv4_len+1; i++){
    printf("Blocked IP address: %s\n",blocked_ipv4_addrs[i].ipv4_addr);
  }
  */
}


void host_mon_parser(){
  FILE * fp = fopen(default_host_conf,"r");
  if(fp == NULL){
    printf("Failed to open %s\n",default_host_conf);
    exit(EXIT_FAILURE);
  }
}
