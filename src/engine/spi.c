// #include "spi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include "../debug.h"
#include "flags.h"

#include "../filter/parsing/rule.h"
#include <pthread.h>

int conversation_exists(struct rule_data * rdata){
  
  for(int i = 0 ; i < total_conversations; i++){
    struct spi_members * sm = &spi_table[i];
    if(rdata->dest_port == sm->cli_port && rdata->src_port == sm->serv_port){
      if(strcmp(rdata->src_ip_addr, sm->server_addr.netaddr) && strcmp(rdata->dest_ip_addr,sm->client_addr.netaddr)){
        return i;
      }
    }
    else if(rdata->src_port == sm->cli_port && rdata->dest_ip_addr == sm->serv_port){
      if(strcmp(rdata->src_ip_addr, sm->client_addr.netaddr) && strcmp(rdata->dest_ip_addr,sm->server_addr.netaddr)){
        return i;
      }
    }
  }  
  return -1;
}


void add_new_conversation(struct rule_data * rdata){
  // int c_cache = total_conversations;
  int location;
  if((location = conversation_exists(rdata)) != -1){
    struct spi_members * sm = &spi_table[location];
    sm->possible_retransmissions++;
    if(debug_mode) printf("SPI TABLE RETRAN %d: %s:%d -> %s:%d\n",
                                  location,sm->client_addr.netaddr,
                                  sm->cli_port, sm->server_addr.netaddr,
                                  sm->serv_port);
  }
  else{
    struct spi_members * member = &spi_table[++total_conversations];
    strcpy(member->client_addr.netaddr,rdata->src_ip_addr);
    strcpy(member->server_addr.netaddr,rdata->dest_ip_addr);
    member->cli_port = rdata->src_port;
    member->serv_port = rdata->dest_port;
    member->protocol = rdata->__protocol;
    member->cli_packet_recv = &member->serv_packet_sent;
    member->cli_packet_sent = &member->serv_packet_recv;
    member->status = __TCP_INIT;
    printf("SPI TABLE ENTRY %d: %s:%d -> %s:%d %d\n",
              total_conversations,
              member->client_addr.netaddr,
              member->cli_port,
              member->server_addr.netaddr,
              member->serv_port,
              member->status);
  }
}