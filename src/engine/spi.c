#include <stdint.h>
#include "spi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include "../debug.h"
#include "flags.h"
#include <pthread.h>
void add_pkt_data(const struct pkt_spi * pdata){
  if(spi_max <= spi_pkt_now){  
   livedebug("spi.c: add_pkt_data: spi_pkt_now = %d",spi_pkt_now);
    // pthread_t pthrd;
    // pthread_create(&pthrd,NULL,&spi_scan,NULL);
    // pthread_join(&pthrd,NULL);
    spi_pkt_now = 0;
    // return;
    
  }
}


void * spi_scan(){
  union addr{
    char * src_ip_addr;
    // char * conversations[50];
    unsigned int current_progress;
    unsigned int teardowns;
    unsigned int inits;
  };
  struct pkt_spi spi_list[200];
  memcpy(spi_list,last_pkts_spi,sizeof(spi_list));
  livedebug("spi.c: spi_scan: {last_pkt_spi: %p; spi_list: %p;}",last_pkts_spi,spi_list);
  union addr addrs[100];
  int addr_len = 0;
  for(int i = 0; i < spi_max; i++ ){
    if(spi_list[i].flags ^ NE_TCP_CONNECT_INIT == 0x0000){
      addrs[addr_len++].src_ip_addr = &spi_list[i].src_ip_addr;
    }
  }
  for(int i = 0; i < addr_len; i++){
    printf("New connection: %s\n",addrs[i].src_ip_addr);
  }
  return (void *)1;
}

void spi_set_value(struct pkt_spi * member, int value){
  if(member->flags == 0x0000)
    member->flags = value;
  else 
    member->flags ^= value;
}


