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
    
//     if(rdata->dest_port > 30000){
//       // server ----> client
      
//     }
// if(rdata->dest_port == tcp_table[i].cli_port &&
//          rdata->src_port == tcp_table[i].serv_port &&
//          strcmp(rdata->dest_ip_addr, tcp_table[i].client_addr) == 0 &&
//          strcmp)
//   }
  }  

  return -1;
}





