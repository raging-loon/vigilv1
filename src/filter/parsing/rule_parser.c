#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rule_parser.h"

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
    printf("%s\n",line);
  }
}

int main(){
  rule_library_parser("../../npsi.conf");
}