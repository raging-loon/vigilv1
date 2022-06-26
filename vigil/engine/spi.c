/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../globals.h"
#include "../filter/parsing/rule.h"
#include "spi.h"
#include <string.h>
#include <stdbool.h>false
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
  if((loc = conversation_exists(rdata)) != -1){
    return &spi_table[loc];
  }
  else {

    return NULL;
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
  // printf("%s:%d -> %s:%d\n",rdata->src_ip_addr,rdata->src_port, rdata->dest_ip_addr, rdata->dest_port);

  for(int i = 0; i < total_conversations + 1; i++){
    struct spi_members * sm = &spi_table[i];
    // printf("%s:%d -> %s:%d\n",sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
    if(sm->conversation_active){
      if(rdata->dest_port == sm->cli_port && rdata->src_port == sm->serv_port){
        if(strcmp(rdata->src_ip_addr, sm->serv_addr) == 0 && 
           strcmp(rdata->dest_ip_addr,sm->cli_addr) == 0){
          if(rdata->__protocol == sm->protocol)
            return i;
        }     
      }
    } else if(rdata->src_port == sm->cli_port && rdata->dest_port == sm->serv_port){
        if(strcmp(rdata->dest_ip_addr,sm->serv_addr) == 0 && 
           strcmp(rdata->src_ip_addr, sm->cli_addr) == 0){
          if(rdata->__protocol == sm->protocol)
            return i;
        }
    }

    // if(strcmp((char *)sm->cli_addr,rdata->src_ip_addr) == 0 ){

    // }
  }
  return -1;
}



struct spi_members * add_new_conversation(struct rule_data * rdata){
  struct spi_members * sm = &spi_table[get_new_spi_loc()];
  memset(sm, 0, sizeof(sm));
  sm->initvar = 0xffff;
  sm->conversation_active = true;
  strcpy((char *)sm->cli_addr,rdata->src_ip_addr);
  strcpy((char *)sm->serv_addr, rdata->dest_ip_addr);
  
  sm->cli_port = rdata->src_port;
  sm->serv_port = rdata->dest_port;
  sm->status = __SPI_UNINIT;
  sm->data_pkt = 0;
  sm->cli_packet_recv = &sm->serv_packet_sent;
  sm->cli_packet_sent = &sm->serv_packet_recv;

  sm->start_time = (unsigned long)time(NULL);

  sm->control_pkt++;
  sm->protocol = rdata->__protocol;
  // printf("SPI NEW CONVERSATION %s %d %s:%d -> %s:%d\n",
            // sm->protocol == R_TCP ? "TCP" : "UDP",
            // total_conversations,
            // sm->cli_addr, sm->cli_port, sm->serv_addr, sm->serv_port);
  return sm;
}



void tcp_spi_handler(struct rule_data * rdata){
  struct spi_members * sm = get_conversation(rdata);

  // printf(":%s ", rdata->tcp_flags);
  if(strncmp((char *)rdata->tcp_flags,"FPU",4) == 0){
    printf("XMAS SCAN ALERT %s:%d -> %s:%d\n", rdata->src_ip_addr, rdata->src_port, rdata->dest_ip_addr, rdata->dest_port);
  } else if(strlen((char *)rdata->tcp_flags) == 0){
    printf("NULL SCAN ALERT %s:%d -> %s:%d\n", rdata->src_ip_addr, rdata->src_port, rdata->dest_ip_addr, rdata->dest_port);
  } else {

    rdata->tcp_flags[strcspn((char *)rdata->tcp_flags,"U")] = '\0';
    if(strcmp((char *)rdata->tcp_flags,"A") == 0){
      tcp_ack_handler(sm);
    }
    else if(strcmp((char * )rdata->tcp_flags,"AS") == 0){
      tcp_syn_ack_handler(sm);
      return;
    }
    else if(strcmp((char *)rdata->tcp_flags, "R") == 0){
      tcp_rst_handler(sm);
    }
    else if(strcmp((char *)rdata->tcp_flags, "AR") == 0){
      // handle RST-ACK
    }
    else if(strcmp((char *)rdata->tcp_flags, "S") == 0){
      sm = add_new_conversation(rdata);


      tcp_syn_handler(sm);
      return;
    }
  }


}

