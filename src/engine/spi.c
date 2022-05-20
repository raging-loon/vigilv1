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
#include <string.h>
#include <time.h>
#include "../../globals.h"
#include "../database/update_db.h"

struct spi_members spi_table[1024];
unsigned int total_conversations = -1;


int conversation_exists(struct rule_data * rdata){
  for(int i = 0; i < total_conversations + 1; ++i){
    struct spi_members * sm = (struct spi_members *)&spi_table[i];
    // printf("sm | %s | %s | %d | %d\n",sm->serv_addr,sm->cli_addr,sm->serv_port,sm->cli_port);
    // printf("rdata | %s | %s | %d | %d\n",rdata->src_ip_addr,rdata->dest_ip_addr,rdata->src_port, rdata->dest_port);
    if(sm->conversation_active != false){
      if(rdata->dest_port == sm->cli_port && rdata->src_port == sm->serv_port){
        if(strcmp(rdata->src_ip_addr, sm->serv_addr) == 0 && strcmp(rdata->dest_ip_addr,sm->cli_addr) == 0){
          return i;
        }
      } else if(rdata->src_port == sm->cli_port && rdata->dest_port == sm->serv_port){
        if(strcmp(rdata->dest_ip_addr, sm->serv_addr) == 0 && strcmp(rdata->src_ip_addr,sm->cli_addr) == 0){
          return i;
        }
      }
    }
    
  }
  return -1;
}

static int get_new_spi_location(){
  if(total_conversations == -1)
    return ++total_conversations;
  
  for(int i = 0; i < total_conversations; ++i){
    if(spi_table[i].conversation_active == false) return i;
  }
  return ++total_conversations;
}

void add_new_conversation(struct rule_data * rdata){
  if(use_spi){
    /*
    struct watchlist_member * w = member_exists(rdata->src_ip_addr);
    w->conversations_started++;
    if(w->conv_ib_time == 0) 
      w->conv_ib_time = (unsigned long)time(NULL);
    else {
      
    }
    */
    int loc = conversation_exists(rdata);
    struct spi_members * sm;

    if(loc != -1){
      sm = &spi_table[loc];
      sm->possible_retransmissions++;
      sm->control_pkt++;
      printf("SPI TABLE RETRANS: %d: %s:%d -> %s:%d\n",loc,sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
    } else {
        sm = &spi_table[get_new_spi_location()];
        memset(sm,0,sizeof(sm));

        sm->conversation_active = true;
        strcpy(sm->cli_addr, rdata->src_ip_addr);
        strcpy(sm->serv_addr, rdata->dest_ip_addr);
        sm->cli_port = rdata->src_port;
        sm->serv_port = rdata->dest_port;
        sm->data_pkt = 0;
        sm->cli_packet_recv = &sm->serv_packet_sent;
        sm->cli_packet_sent = &sm->serv_packet_recv;
        increment_stats(rdata,sm);
        
        sm->start_time = (unsigned long)time(NULL);
        sm->control_pkt = 0;
        sm->control_pkt++;
        sm->protocol = rdata->__protocol;
        printf("SPI NEW CONV: %d: %s:%d -> %s:%d\n",total_conversations,sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
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
    sm->control_pkt++;
    increment_stats(rdata,sm);
    printf("SPI TWH 2/3: %d: %s:%d -> %s:%d\n",loc,rdata->src_ip_addr,rdata->src_port,rdata->dest_ip_addr,rdata->dest_port);
    if(sm->status == __TCP_INIT) sm->status = __TCP_ACK_W;
  }
}

/* Handles packets with ACK as the only flag set */
void update_table(struct rule_data * rdata){
  int loc = conversation_exists(rdata);
  if(loc != -1){
    struct spi_members * sm = &spi_table[loc];
    sm->control_pkt++;
    increment_stats(rdata,sm);
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
        sm->end_time = (unsigned long)time(NULL);
        pthread_t pthrd;
        pthread_create(&pthrd,NULL,&update_spi_db,sm);
        pthread_join(pthrd,NULL);
  
    }
  }
}

void polite_end(struct rule_data * rdata){
  int loc = conversation_exists(rdata);
  if(loc != -1){
    
    struct spi_members * sm = &spi_table[loc];
    sm->control_pkt++;
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
    increment_stats(rdata,sm);
  }

}

void handle_data_pkt(struct rule_data * rdata){
  int loc = conversation_exists(rdata);
  if(loc != -1){
    struct spi_members * sm = &spi_table[loc];
    sm->data_pkt++;
    increment_stats(rdata,sm);
  }
}
void increment_stats(struct rule_data * rdata, struct spi_members * sm){
  if(strcmp(rdata->src_ip_addr,sm->cli_addr) == 0){
    sm->serv_packet_recv++;
  } else if(strcmp(rdata->src_ip_addr,sm->serv_addr) == 0){
    sm->serv_packet_sent++;
  }
}