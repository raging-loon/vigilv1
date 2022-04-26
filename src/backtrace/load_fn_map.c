#include <stdio.h>
#include "backtrace.h"
#include <stdlib.h>
#include <string.h>
#include "../../main.h"
#include "../capture/tcpmgr.h"
#include "../capture/pktmgr.h"
void add_fn(char * name, unsigned int start, unsigned int end){
  fn_mem_loc * fn = &fn_mem_map[fn_num++];
  strcpy(fn->fn_name,name);
  fn->start = start;
  fn->end = end;
}

void print_mem_map(){
  for(int i = 0; i < fn_num; i++){
    fn_mem_loc * fn = &fn_mem_map[i];
    printf("%s [start %d] [end %d]\n",fn->fn_name,fn->start,fn->end);
  } 
}

void load_fn_mem_map(){
  FILE * fp = fopen("/usr/share/vigil/memmap.txt","r");
  if(fp == NULL){
    printf("FATAL ERROR: memmap.txt not found."
          "Please re run gen_mem_map.py and copy memmap.txt to /usr/share/vigil\n");
    exit(-1);
  }
  char * line = NULL;
  size_t pos, len = 0;
  while((pos = getline(&line,&len,fp)) != -1){
    line[strcspn(line,'\n')] = 0;
    char * name;
    unsigned int start;
    unsigned int end;
    int num_parsed = 0;
    char * token = strtok(line, " ");
    while(token != NULL){
      switch(num_parsed){
        case 0:
          name = token;
          break;
        case 1:
          start = atoi(token);
          break;
        case 2:
          end = atoi(token);
          break;
        default:
          break;
      }
      token = strtok(NULL," ");
      num_parsed++;
    }
    add_fn(name,start,end);
  }
}


