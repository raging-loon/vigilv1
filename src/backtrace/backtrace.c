/*
 * Copyright 2021-2022 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */


#include "backtrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include "../utils.h"

fn_mem_loc fn_mem_map[TOTAL_FN];
int fn_num = 0;
void print_mem_map(){
  for(int i = 0; i < fn_num; i++){
    fn_mem_loc * fn = &fn_mem_map[i];
    printf("[N %s S 0x%02x E 0x%02x]\n",fn->fn_name, fn->start,fn->end);
  }
}

void crash_handler(int sig){
  register unsigned int const r_rax __asm__("rax");
  register unsigned int const r_rbx __asm__("rbx");
  register unsigned int const r_rcx __asm__("rcx");
  register unsigned int const r_rdx __asm__("rdx");
  register unsigned int const r_rsp __asm__("rsp");
  register unsigned int const r_rbp __asm__("rbp");
  
  void * array[20];
  char ** strings;
  int size = backtrace(array, 20);
  strings = backtrace_symbols(array,size);
  printf("Segmentation fault at %s: application crashed\n",get_formated_time());
  printf("Function backtrace:\n");
  if(strings != NULL){
    for(int i = 0; i < size; i++){
      if(strstr(strings[i],"lib") != NULL){
        // printf("Library function: %s\n",strings[i]);
        continue;
      } else {
        char temp_offset[24];
        unsigned int offset;
        sprintf(temp_offset,"%s\n",strings[i] + strloc(strings[i],'+') + 1);
        temp_offset[strloc(temp_offset,')') ] = 0;
        offset = strtol(temp_offset,NULL,16);
        fn_mem_loc * fn = offset_search(offset);
        if(offset != NULL){
          printf("[N %s S 0x%02x E 0x%02x (./vigil.exe(+0x%02x))]\n",fn->fn_name, fn->start, fn->end, offset);
        } else {
          printf("Unknown function at memory offset 0x%02x\n",offset);
        }
      }

    }
  }
  free(strings);
  
  // print_mem_map();
  printf("Register Dump:\n");
  printf("[RAX] = 0x%02x\n",r_rax);
  printf("[RBX] = 0x%02x\n",r_rbx);
  printf("[RCX] = 0x%02x\n",r_rcx);
  printf("[RDX] = 0x%02x\n",r_rdx);
  printf("[RSP] = 0x%02x\n",r_rsp);
  printf("[RBP] = 0x%02x\n",r_rbp);

  exit(EXIT_FAILURE); 

}


fn_mem_loc * offset_search(unsigned int offset){
  for(int i = 0; i < fn_num; i++){
    fn_mem_loc * fn = &fn_mem_map[i];
    if(offset > fn->start && offset < fn->end) return fn;
  }
  return NULL;
}