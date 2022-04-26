#include "backtrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include "../utils.h"

fn_mem_loc fn_mem_map[TOTAL_FN];
int fn_num = 0;
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
      printf("%s\n",strings[i]);
    }
  }
  free(strings);
  // print_mem_map();
  printf("Register Dump:\n");
  printf("[RAX] = 0x%02x\n",r_rax);
  printf("[RBX] = 0x%02x\n",r_rbx);
  printf("[RCX] = 0x%02x\n",r_rbx);
  printf("[RDX] = 0x%02x\n",r_rcx);
  printf("[RSP] = 0x%02x\n",r_rsp);
  printf("[RBP] = 0x%02x\n",r_rbp);
  printf("%p\n",crash_handler);
  printf("0x%02x\n",r_rbp - r_rsp);
  exit(EXIT_FAILURE); 

}
