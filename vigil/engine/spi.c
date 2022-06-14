#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../globals.h"
#include "../filter/parsing/rule.h"
#include "spi.h"
#include <string.h>
#include "../database/update_db.h"

struct spi_members spi_table[1024];
unsigned int total_conversations = -1;

static int get_new_spi_loc(){
  if(total_conversations == -1) return ++total_conversations;
  for(int i = 0; i < total_conversations; i++)
    if(spi_table[i].conversation_active == false) return i;
  return ++total_conversations;
}

static struct spi_members * get_conversation(struct rule_data * rdata){
  int loc;
  if((loc = conversation_exists(rdata)) != -1)
    return &spi_table[loc];
  else {
    
    return &spi_table[get_new_spi_loc()];

  }
}

void spi_handler(struct rule_data * rdata){
  switch(rdata->__protocol){
    case R_TCP:
      tcp_spi_handler(rdata);
      break;
    default:
      printf("Unknown protocol for SPI\n");
      break;
  }
}

int conversation_exists(struct rule_data * rdata){
  for(int i = 0; i < total_conversations + 1; i++){
    struct spi_members * sm = &spi_table[i];
    if(!sm->conversation_active){
      if(rdata->dest_port == sm->cli_port && rdata->src_port == sm->serv_port){
        if(strcmp(rdata->src_ip_addr, (const char *)sm->serv_addr) == 0 && strcmp(rdata->dest_ip_addr,(const char *)sm->cli_addr)){
          return i;
        }     
      }
    } else if(rdata->src_port == sm->cli_port && rdata->dest_port == sm->serv_port){
        if(strcmp(rdata->dest_ip_addr,(const char *)sm->serv_addr) == 0 && strcmp(rdata->src_ip_addr, (const char *)sm->cli_addr) == 0){
          return i;
        }
    }


  }
  return -1;
}



void add_new_conversation(struct rule_data * rdata){
  struct spi_members * sm = get_conversation(rdata);
  if(sm->initvar == 0xffff) return;
  memset(sm, 0, sizeof(sm));
  sm->initvar = 0xffff;
  sm->conversation_active = true;
  strcpy((char *)sm->cli_addr,rdata->src_ip_addr);
  strcpy((char *)sm->serv_addr, rdata->dest_ip_addr);

  sm->cli_port = rdata->src_port;
  sm->serv_port = rdata->dest_port;
  
  sm->data_pkt = 0;
  sm->cli_packet_recv = &sm->serv_packet_sent;
  sm->cli_packet_sent = &sm->serv_packet_recv;

  sm->start_time = (unsigned long)time(NULL);

  sm->control_pkt++;
  sm->protocol = rdata->__protocol;
  printf("SPI NEW CONVERSATION %s %d %s:%d -> %s:%d\n",
            sm->protocol == R_TCP ? "TCP" : "UDP",
            total_conversations,
            sm->cli_addr, sm->cli_port, sm->serv_addr, sm->serv_port);
  if(sm->protocol == R_TCP) sm->status = __TCP_INIT;
}



void tcp_spi_handler(struct rule_data * rdata){
  struct spi_members * sm = get_conversation(rdata);

}

