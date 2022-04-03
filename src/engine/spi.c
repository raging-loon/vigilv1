/*
 * Copyright 2021-2022 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#include <stdlib.h>
#include <stdio.h>
#include "../statistics/watchlist.h"
#include <string.h>
#include "../../globals.h"

int conversation_exists(struct rule_data * rdata){
  for(int i = 0; i < total_conversations + 1; ++i){
    struct spi_members * sm = (struct spi_members *)&spi_table[i];
    if(sm->conversation_active != false){
      if(rdata->dest_port == sm->cli_port && rdata->src_port == sm->serv_port){
        if(strcmp(rdata->src_ip_addr, sm->serv_addr.netaddr) == 0 && strcmp(rdata->dest_ip_addr,sm->cli_addr.netaddr) == 0){
          return i;
        }
      } else if(rdata->src_port == sm->cli_port && rdata->dest_port == sm->serv_port){
        if(strcmp(rdata->dest_ip_addr, sm->serv_addr.netaddr) == 0 && strcmp(rdata->src_ip_addr,sm->cli_addr.netaddr) == 0){
          return i;
        }
      }
    }
    
  }
  return -1;
}

static int get_new_spi_location(){
  for(int i = 0; i < total_conversations - 1; ++i){
    if(spi_table[i].conversation_active == false) return i;
  }
  return total_conversations++;
}

void add_new_conversation(struct rule_data * rdata){
  if(use_spi){
    struct watchlist_member * w = member_exists(rdata->src_ip_addr);
    w->conversations_started++;
    if(w->conv_ib_time == 0) 
      w->conv_ib_time = (unsigned long)time(NULL);
    else {
      /*
        first packet = 1000s
        second packets = 2000s
        
      
      */
    }

    int loc = conversation_exists(rdata);
    struct spi_members * sm;

    if(loc != -1){
      sm = &spi_table[loc];
      sm->possible_retransmissions++;
      printf("SPI TABLE RETRANS: %d: %s:%d -> %s:%d\n",loc,sm->cli_addr.netaddr,sm->cli_port,sm->serv_addr.netaddr,sm->serv_port);
    } else {
        sm = &spi_table[++total_conversations];
        memset(sm,0,sizeof(sm));
        sm->conversation_active = true;
        strcpy(sm->cli_addr.netaddr, rdata->src_ip_addr);
        strcpy(sm->serv_addr.netaddr, rdata->dest_ip_addr);
        sm->cli_port = rdata->src_port;
        sm->serv_port = rdata->dest_port;
        sm->data_pkt = 0;
        sm->control_pkt = 0;
        printf("SPI NEW CONV: %d: %s:%d -> %s:%d\n",total_conversations,sm->cli_addr.netaddr,sm->cli_port,sm->serv_addr.netaddr,sm->serv_port);
        if(rdata->__protocol == R_TCP){
          sm->status = __TCP_INIT;
        }
      
    }
  }
}


void spi_ud_thw(struct rule_data * rdata){
  int loc = conversation_exists(rdata);
  if(loc != -1){

    struct spi_members * sm = &spi_table[loc];
    printf("SPI TWH 2/3: %d: %s:%d -> %s:%d\n",loc,rdata->src_ip_addr,rdata->src_port,rdata->dest_ip_addr,rdata->dest_port);
    if(sm->status == __TCP_INIT) sm->status = __TCP_ACK_W;
  }
}

/* Handles packets with ACK as the only flag set */
void update_table(struct rule_data * rdata){
  int loc = conversation_exists(rdata);
  if(loc != -1){
    struct spi_members * sm = &spi_table[loc];
    if(sm->status == __TCP_ACK_W){
      sm->status = __TCP_ESTABLISHED;
      printf("SPI ENTRY: %d: SESSION EST: %s:%d -> %s:%d\n",
        loc,
        rdata->src_ip_addr,
        rdata->src_port,
        rdata->dest_ip_addr,
        rdata->dest_port);
    } else if(sm->status == __TCP_FIN_INIT2){
        printf("SPI ENTRY: %d: POLITE CONV END 3/3: %s:%d -> %s:%d\n",
          loc,
          rdata->src_ip_addr,
          rdata->src_port,
          rdata->dest_ip_addr,
          rdata->dest_port);
        sm->status = __TCP_CLOSED_FIN;
        sm->conversation_active = false;
    }
  }
}

void polite_end(struct rule_data * rdata){
  int loc = conversation_exists(rdata);
  if(loc != -1){
    
    struct spi_members * sm = &spi_table[loc];
    if(sm->status == __TCP_FIN_INIT){
      printf("SPI ENTRY: %d: POLITE CONV END 2/3: %s:%d -> %s:%d\n",
        loc,
        rdata->src_ip_addr,
        rdata->src_port,
        rdata->dest_ip_addr,
        rdata->dest_port);     
      sm->status = __TCP_FIN_INIT2;
    }
    else {
      printf("SPI ENTRY: %d: POLITE CONV END 1/3: %s:%d -> %s:%d\n",
        loc,
        rdata->src_ip_addr,
        rdata->src_port,
        rdata->dest_ip_addr,
        rdata->dest_port);
      sm->status = __TCP_FIN_INIT;

    }
  }

}