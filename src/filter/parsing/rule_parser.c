#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rule_parser.h"
static bool is_rule(const char *);
static bool is_comment(const char * line);
static void rstrip(char * );


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

static void rule_parser(const char * __filename){
  // + 1 for the $ at the beggining
  char * filename = __filename + 1;
  
  FILE * fp = fopen(filename,"r");
  if(fp == NULL){
    printf("Error opening rule file: %s. Refusing to continue\n",filename);
    exit(EXIT_FAILURE);
  }
  
  size_t pos;
  size_t len = 0;
  char * line = NULL;
  while((pos = getline(&line,&len,fp)) != -1){
    if(is_comment(line))
      continue;
    rstrip(line);
    printf("%s\n",line);
  }
}



