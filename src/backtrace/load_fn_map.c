#include <stdio.h>
#include "backtrace.h"
#include <stdlib.h>
#include <string.h>
#include "../../main.h"


void add_fn(void * fn, char * fn_name){
  fn_mem_loc * fn_loc = &fn_mem_map[fn_num++];
  strcpy(fn_loc->fn_name,fn_name);
  sprintf(fn_loc->mem_loc,"%p",fn);
}

void print_mem_map(){
  printf("Program memory mapping:\n");
  for(int i = 0; i < fn_num; i++){
    printf("%s [%s]\n",fn_mem_map[i].fn_name,fn_mem_map[i].mem_loc);
  }  
}

void load_fn_mem_map(){
  add_fn(main,"main");
}

