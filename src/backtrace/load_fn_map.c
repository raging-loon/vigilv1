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
  
}

void load_fn_mem_map(){
  
}


