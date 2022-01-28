// #include "spi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include "../debug.h"
#include "flags.h"
#include "../logging.h"
#include "../utils.h"
#include <time.h>
#include "../filter/parsing/rule.h"
#include <pthread.h>

spi_info conversation_exists(struct rule_data * rdata){
  spi_info info;
  // printf("%s:%d -> %s:%d | ",rdata->src_ip_addr,rdata->src_port, rdata->dest_ip_addr,rdata->dest_port);
  for(int i = 0 ; i < total_conversations + 1; ++i){
    struct spi_members * sm = (struct spi_members *)&spi_table[i];
    if(sm->status != __TCP_CLOSED_FIN && sm->status != __TCP_CLOSED_RST){

      // printf("%s:%d -> %s:%d\n", sm->client_addr.netaddr, sm->cli_port, sm->server_addr.netaddr,sm->serv_port);
      if(rdata->dest_port == sm->cli_port && rdata->src_port == sm->serv_port){
        // printf("src\n");
        if(strcmp(rdata->src_ip_addr, sm->server_addr.netaddr) == 0 && strcmp(rdata->dest_ip_addr,sm->client_addr.netaddr) == 0){
          info.direction = DIR_SERVER_TO_CLIENT;
          info.table_location = i;
          return info;
        }
      }
      else if(rdata->src_port == sm->cli_port && rdata->dest_port == sm->serv_port){
        // printf("dest\n");
        if(strcmp(rdata->src_ip_addr, sm->client_addr.netaddr) == 0 && strcmp(rdata->dest_ip_addr,sm->server_addr.netaddr) == 0){
          info.direction = DIR_CLIENT_TO_SERVER;
          info.table_location = i;
          return info;
        }
      }
    }
  }  
  info.table_location = -1;
  return info;
}


void add_new_conversation(struct rule_data * rdata){
  // int c_cache = total_conversations;
  int location;
  spi_info info = conversation_exists(rdata);
  if(info.table_location != -1){
    struct spi_members * sm = &spi_table[info.table_location];
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
    member->start_time = (unsigned long )time(NULL);
    printf("SPI TABLE ENTRY %d: %s:%d -> %s:%d %d\n",
              total_conversations,
              member->client_addr.netaddr,
              member->cli_port,
              member->server_addr.netaddr,
              member->serv_port,
              member->status);
  }
}

void update_table(struct rule_data * rdata){
  
  spi_info info = conversation_exists(rdata);
  if(info.table_location != -1){
    struct spi_members * sm = &spi_table[info.table_location];
    if(sm->status == __TCP_ACK_W){
      sm->status = __TCP_ESTABLISHED;
      if(debug_mode) printf("SPI CONNECTION EST %d: %s:%d -> %s:%d %d\n",
              total_conversations,
              sm->client_addr.netaddr,
              sm->cli_port,
              sm->server_addr.netaddr,
              sm->serv_port,
              sm->status);
    } else {
      if(sm->status == __TCP_FIN_INIT2){
        sm->status == __TCP_CLOSED_FIN;
        printf("SPI CONNECTION CLOSED %d: %s:%d -> %s:%d\n", 
                  info.table_location,sm->client_addr.netaddr, sm->cli_port,
                  sm->server_addr.netaddr, sm->serv_port);
      }
      update_information(sm,&info);
    }
    update_information(sm,&info);
  } else {
    printf("Suspect packet recv\n");
  } 
}

void update_information(struct spi_members * sm, spi_info * info){
  if(info->direction == DIR_CLIENT_TO_SERVER){
      sm->cli_packet_sent++;
      sm->serv_packet_recv++;
    } else {
      sm->serv_packet_sent++;
      sm->cli_packet_recv++;
    }
}

// use for sn ack
void spi_ud_thw(struct rule_data * rdata){
  spi_info info = conversation_exists(rdata);
  if(info.table_location != -1){
    struct spi_members * sm = &spi_table[info.table_location];
    if(sm->status == __TCP_INIT){
      sm->status = __TCP_ACK_W;
    } 
  } else {
    printf("Suspect packet recvd\n");
  }
}


void end_connection(struct rule_data * rdata){
  spi_info info = conversation_exists(rdata);
  if(info.table_location != -1){
    struct spi_members * sm = &spi_table[info.table_location];
    update_information(sm,&info);
    if(sm->status == __TCP_FIN_INIT) sm->status = __TCP_FIN_INIT2;
    else sm->status = __TCP_FIN_INIT;
  } else {
    FILE * fp = fopen("/var/log/siglog.log","a");
    lprintf(fp,"%s %s:%d -> %s:%d FIN Portscan\n",
                    get_formated_time(),
                    rdata->src_ip_addr,rdata->src_port,
                    rdata->dest_ip_addr,rdata->dest_port);
    fclose(fp);
  }
}