#include "ip_addr_stat.h"
#include <stdbool.h>
// #include <threads.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include <stdlib.h>
void add_ip_addr_or_inc_counter(const char * ip_addr){
  char cpy_ip_addr[24];
  memset(&cpy_ip_addr,0,sizeof(cpy_ip_addr));
  
  pthread_t pthrd;
  aiaoic_args * args = (aiaoic_args*)malloc(sizeof(aiaoic_args));
  strncpy(cpy_ip_addr,ip_addr,strlen(ip_addr));
  // printf("[DEBUG] cpy_ip_addr = %s\n",cpy_ip_addr); 

  memcpy((char*)&args->__ip_addr,(char*)&cpy_ip_addr,sizeof(cpy_ip_addr));
  // printf("[DEBUG] aiaoic = %p\n",args->__ip_addr);
  // printf("[DEBUG] aiaoic = %s\n",args->__ip_addr);

  pthread_create(&pthrd, NULL, &verify_ip_addr, (void *)&args->__ip_addr);
  pthread_join(pthrd, NULL);

}



static void* verify_ip_addr(void * args){
  // aiaoic_args * temp_info = args;//(aiaoic_args*)malloc(sizeof(aiaoic_args));
  const char * ip_addr = args;
  // printf("[DEBUG] aiaoic_args = %s\n",temp_info->__ip_addr);
  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    if(strcmp(ip_addr , ip_stats[i].ip_addr) == 0){
      // printf("Found match: %s == %s\n",ip_addr,ip_stats[ip_addr_stat_counter_len].);
      ip_stats[i].count++;
      goto end; 
    }
  }
  struct ip_addr_counter * temp_stat = (struct ip_addr_counter*)malloc(sizeof(struct ip_addr_counter));
  ip_stats[++ip_addr_stat_counter_len] = (struct ip_addr_counter)*temp_stat;
  memset(temp_stat->ip_addr,0,sizeof(ip_addr));
  strcpy(ip_stats[ip_addr_stat_counter_len].ip_addr,ip_addr);
  ip_stats[ip_addr_stat_counter_len].count++;
  // printf("[DEBUG] temp_info->__ip_addr = %s ip_stats[ip_addr_stat_counter_len].ip_addr = %s\n",temp_info->__ip_addr,ip_stats[ip_addr_stat_counter_len].ip_addr);
  
end:;
  
}
