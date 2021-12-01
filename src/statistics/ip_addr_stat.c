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
  struct aiaoic_args * args = malloc(sizeof(aiaoic_args));

  pthread_create(&pthrd, NULL, &verify_ip_addr, &args);

}



static void *verify_ip_addr(void * args){
  // const char * ip_addr = ((struct aiaoic_args*)&args)->__ip_addr;
  aiaoic_args * temp_info = args;
  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    if(strcmp(temp_info->__ip_addr , ip_stats[ip_addr_stat_counter_len].ip_addr)){
      ip_stats[i].count++;
      goto end; 
    }
  }
  struct ip_addr_stat temp_stat;
  ip_stats[++ip_addr_stat_counter_len] = temp_stat;
  strcpy(ip_stats[ip_addr_stat_counter_len].ip_addr,temp_info->__ip_addr);
  ip_stats[ip_addr_stat_counter_len].count++;
end:;
}
