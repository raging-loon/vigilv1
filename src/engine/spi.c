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
  int server_port, client_port;
  char * server_addr;
  char * client_addr;

  for(int i = 0 ; i < total_conversations; i++){
    
  }  

  return -1;
}


void add_new_conversation(struct rule_data * rdata){
  // int c_cache = total_conversations;
  struct spi_members * member = &spi_members[++total_conversations];
  strcpy(member->client_addr,rdata->src_ip_addr);
  strcpy(member->server_addr,rdata->dest_ip_addr);
  member->cli_port = rdata->src_port;
  member->serv_port = rdata->dest_port;
  member->protocol = rdata->__protocol;
  member->cli_packet_recv = &member->serv_packet_sent;
  member->cli_packet_sent = &member->serv_packet_recv;
  member->status = TCP_INIT;
}