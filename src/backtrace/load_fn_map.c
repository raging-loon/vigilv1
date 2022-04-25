#include <stdio.h>
#include "backtrace.h"
#include <stdlib.h>
#include <string.h>



void add_fn(void * fn, char * fn_name){
  fn_mem_loc * fn_loc = &fn_mem_map[fn_num++];
  strcpy(fn_loc->fn_name,fn_name);
  sprintf(fn_loc->mem_loc,"%p",fn);
}

void load_fn_mem_map(){

}