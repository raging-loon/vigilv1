#include "ip_addr_stat.h"
#include <stdbool.h>
// #include <threads.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include "../capture/protocols.h"
#include <stdlib.h>
void add_ip_addr_or_inc_counter(const char * ip_addr,bool __is_src,int __traffic_type){
  // printf("[DEBUG] ip_addr = %s\n",ip_addr);
  char cpy_ip_addr[24];
  memset(&cpy_ip_addr,0,sizeof(ip_addr));
  
  pthread_t pthrd;
  aiaoic_args args;// = (aiaoic_args*)malloc(sizeof(aiaoic_args));
  memset(&args,0,sizeof(aiaoic_args));
  strncpy(cpy_ip_addr,ip_addr,sizeof(cpy_ip_addr));
  memset(&args,0,sizeof(args));
  strcpy((char*)&args.__ip_addr,(char*)&cpy_ip_addr);//,sizeof(cpy_ip_addr));
  //
  //  printf("[DEBUG] aiaoic = %p\n",args->__ip_addr);
  // printf("[DEBUG] aiaoic = %s\n",args.__ip_addr);
  args.is_src = __is_src;
  args.traffic_type = __traffic_type;
  pthread_create(&pthrd, NULL, &verify_ip_addr, &args);
  pthread_join(pthrd, NULL);

}



static void* verify_ip_addr(void * args){
  aiaoic_args * temp_info = args;//(aiaoic_args*)malloc(sizeof(args));
  // const char * ip_addr = args;
  // temp_info = args;
  // printf("[DEBUG] traffic_class = %d\n",temp_info->traffic_type);
  // printf("[DEBUG] aiaoic_args = %s\n",temp_info->__ip_addr);
  struct ip_addr_counter * temp;
  for(int i = 0; i <= ip_addr_stat_counter_len; i++){
    if(strcmp(temp_info->__ip_addr , ip_stats[i].ip_addr) == 0){
      // printf("Found match: %s == %s\n",ip_addr,ip_stats[ip_addr_stat_counter_len].);
      ip_stats[i].count++;
      temp = &ip_stats[i];
      goto end; 
    }
  }
  struct ip_addr_counter * temp_stat = (struct ip_addr_counter*)malloc(sizeof(struct ip_addr_counter));
  ip_stats[++ip_addr_stat_counter_len] = (struct ip_addr_counter)*temp_stat;
  
  memset(temp_stat->ip_addr,0,sizeof(temp_info->__ip_addr));
  strcpy(ip_stats[ip_addr_stat_counter_len].ip_addr,temp_info->__ip_addr);
  temp = &ip_stats[ip_addr_stat_counter_len];
end:  

  if(temp_info->is_src)
    temp->total_sent++;
  else
    temp->total_recv++;

  temp->count++;
  switch(temp_info->traffic_type){
    case TCP:
      if(temp_info->is_src)
        temp->tcp_sent++;
      else 
        temp->tcp_recv++;
      break;
    case UDP:
      if(temp_info->is_src)
        temp->udp_sent++;
      else 
        temp->udp_recv++;
      break;
    case ICMP:
      if(temp_info->is_src)
        temp->icmp_sent++;
      else 
        temp->icmp_recv++;
      break;
    default:
      if(temp_info->is_src)
        temp->unknown_sent++;
      else
        temp->unknown_recv++;
      break;
  }

  // printf("[DEBUG] temp_info->__ip_addr = %s ip_stats[ip_addr_stat_counter_len].ip_addr = %s\n",temp_info->__ip_addr,ip_stats[ip_addr_stat_counter_len].ip_addr);
  

  
}
