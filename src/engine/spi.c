#include <stdint.h>
#include "spi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include "../debug.h"
#include "flags.h"
#include <pthread.h>

int conversation_exists(const struct rule_data * rdata){
  for(int i = 0 ; i < total_conversations; i++){
    
    if(strcmp(rdata->dest_port > 30000 ? rdata->src_ip_addr : rdata->dest_ip_addr,tcp_table[i].server_addr) &&
       strcmp(rdata->dest_port < 29999 ? rdata->dest_ip_addr : rdata->src_ip_addr, tcp_table[i].client_addr) &&
       (rdata->dest_port == tcp_table[i].serv_port || rdata->src_port == tcp_table[i].serv_port) &&
       (rdata->dest_port == tcp_table[i].cli_port || rdata->src_port == tcp_table[i].cli_port)){
         return i;
       }    
  }  

  return -1;
}





