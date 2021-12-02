#include "ip_addr_stat.h"
#include <stdbool.h>
// #include <threads.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include <stdlib.h>

static __thread char stat_buffer[24];

void add_ip_addr_or_inc_counter(const char * ip_addr){
  // char cpy_ip_addr[24];
  // memset(&cpy_ip_addr,0,sizeof(cpy_ip_addr));
  
  pthread_t pthrd;
  aiaoic_args * args = (aiaoic_args*)malloc(sizeof(aiaoic_args));
  memset(args->__ip_addr,0,sizeof(args->__ip_addr));
  strncpy(stat_buffer,ip_addr,strlen(ip_addr));
  // printf("[DEBUG] cpy_ip_addr = %s\n",cpy_ip_addr);
  
  // strncat((char*)&args->__ip_addr,(char*)&stat_buffer,strlen((char *)&cpy_ip_addr));
  args->__ip_addr = stat_buffer;
  // printf("[DEBUG] aiaoic = %p\n",args->__ip_addr);
  // printf("[DEBUG] aiaoic = %s\n",args->__ip_addr);

  pthread_create(&pthrd, NULL, &verify_ip_addr, (aiaoic_args *)&args);
  pthread_join(pthrd, NULL);

}



static void* verify_ip_addr(void * args){
  // const char * ip_addr = ((struct aiaoic_args*)&args)->__ip_addr;
  aiaoic_args * temp_info = (aiaoic_args*)malloc(sizeof(aiaoic_args));
  temp_info = args;
  printf("[DEBUG] aiaoic_args = %s\n",temp_info->__ip_addr);
  // printf("[DEBUG] aiaoic_args = %p\n",temp_info->__ip_addr);
  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    if(strcmp(temp_info->__ip_addr , ip_stats[ip_addr_stat_counter_len].ip_addr) == 0){
      ip_stats[i].count++;
      // free(temp_info);
      goto end; 
    }
  }
  struct ip_addr_counter * temp_stat = (struct ip_addr_counter*)malloc(sizeof(struct ip_addr_counter));
  ip_stats[++ip_addr_stat_counter_len] = (struct ip_addr_counter)*temp_stat;
  memset(temp_stat->ip_addr,0,sizeof(temp_info->__ip_addr));
  strcpy(ip_stats[ip_addr_stat_counter_len].ip_addr,temp_info->__ip_addr);
  ip_stats[ip_addr_stat_counter_len].count++;
  // printf("[DEBUG] temp_info->__ip_addr = %s ip_stats[ip_addr_stat_counter_len].ip_addr = %s\n",temp_info->__ip_addr,ip_stats[ip_addr_stat_counter_len].ip_addr);
  // free(temp_info);
end:;
  // if(temp_info->__ip_addr)
    // free(temp_info->__ip_addr);
  // if(temp_info)

}
