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
    if(is_rule(line)){
      printf("Parsing: %s\n",line);
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

static void rule_parser(const char * __filename){
  // + 1 for the $ at the beggining
  char * filename = __filename + 1;
  struct rule*  __rule;
  FILE * fp = fopen(filename,"r");
  if(fp == NULL){
    printf("Error opening rule file: %s. Refusing to continue\n",filename);
    exit(EXIT_FAILURE);
  }
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
    // printf("%s\n",line);
    if(strstr(line,"RULE_START{")){
      parsing_rule = true;
    }
    
    else if(strstr(line,"name=\"") != NULL){
      if(!parsing_rule) syntax_error(line,lines);
      // maybe add more flexibility with tabbing and stuff
      char * name = line + 8;
      name[strcspn(name,"\"")] = 0;
      strcpy(__rule->rulename,name);
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
  rules[num_rules++] = *(struct rule *)__rule;
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