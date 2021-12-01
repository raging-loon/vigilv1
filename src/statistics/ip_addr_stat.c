#include "ip_addr_stat.h"
#include <stdbool.h>
// #include <threads.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include <stdlib.h>
void add_ip_addr_or_inc_counter(const char * ip_addr){
  pthread_t pthrd;
  aiaoic_args * args = malloc(sizeof(aiaoic_args));
  // args->__ip_addr = (char *)ip_addr;
  strcpy(args->__ip_addr,ip_addr);
  printf("[DEBUG] aiaoic = %s\n",ip_addr);

  pthread_create(&pthrd, NULL, &verify_ip_addr, &args);

}



static void* verify_ip_addr(void * args){
  // const char * ip_addr = ((struct aiaoic_args*)&args)->__ip_addr;
  aiaoic_args * temp_info = args;
  printf("[DEBUG] aiaoic_args = %s\n",temp_info->__ip_addr);

  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    if(strcmp(temp_info->__ip_addr , ip_stats[ip_addr_stat_counter_len].ip_addr) == 0){
      ip_stats[i].count++;
      // free(temp_info);
      goto end; 
    }
  }
  struct ip_addr_counter * temp_stat = (struct ip_addr_counter*)malloc(sizeof(struct ip_addr_counter));
  ip_stats[++ip_addr_stat_counter_len] = (struct ip_addr_counter)*temp_stat;
  
  strcpy(ip_stats[ip_addr_stat_counter_len].ip_addr,temp_info->__ip_addr);
  ip_stats[ip_addr_stat_counter_len].count++;
  printf("[DEBUG] temp_info->__ip_addr = %s ip_stats[ip_addr_stat_counter_len].ip_addr = %s\n",temp_info->__ip_addr,ip_stats[ip_addr_stat_counter_len].ip_addr);
  // free(temp_info);
end:;
}
