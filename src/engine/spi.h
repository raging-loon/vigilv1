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
#ifndef __SPI_H
#define __SPI_H



#include "../filter/parsing/rule.h"
#include "engine.h"


#define __TCP_LISTENING       240
#define  __TCP_ESTABLISHED    241 /* ACK - end of twh*/
#define  __TCP_FINISHED       242      
#define  __TCP_INIT           243 /* SYN */
#define  __TCP_ACK_W          244 /* SYN/ACK */
#define  __TCP_FIN_INIT       245 /* FIN/ACK */
#define  __TCP_FIN_INIT2      246 /* ACK */
#define  __TCP_RST_COMP       247
#define  __TCP_RST_INIT       248
#define  __TCP_RST_INIT2      249
#define  __TCP_CLOSED_FIN     250
#define  __TCP_CLOSED_RST     251
#define  __UDP_FIRST_SEEN     252
#define  __ICMP_FIRST_SEEN    253



struct spi_members{
  unsigned char serv_addr[41];
  unsigned char cli_addr[41];
  unsigned int serv_port;
  unsigned int cli_port;
  int serv_packet_sent;
  int serv_packet_recv;
  // the following pointers are pointers to the two above, 
  // they only exist to make this easier to write.
  int * cli_packet_sent; 
  int * cli_packet_recv; 

  unsigned int data_pkt, control_pkt;

  int num_cli_rules;
  int num_srv_rules;
  unsigned int status;
  unsigned long start_time;
  unsigned long end_time;
  unsigned int total_packets;
  unsigned int protocol;
  unsigned int pps; /* Packets per second */
  int possible_retransmissions;
  bool conversation_active;
};


typedef struct{
  int table_location;
  int direction;
#define DIR_CLIENT_TO_SERVER        100
#define DIR_SERVER_TO_CLIENT        101
} spi_info;



int conversation_exists(struct rule_data *);

void add_new_conversation(struct rule_data *);
void polite_end(struct rule_data *);
void reset_end(struct rule_data *);
void update_table(struct rule_data *);
// void add_pkt_data(const struct spi_tcp_table *);
void spi_ud_thw(struct rule_data *);
void handle_data_pkt(struct rule_data *);
// void update_information(struct spi_members *, spi_info *);
// void table_roll_over();
// void end_connection(struct rule_data *);
// void * spi_scan();
void increment_stats(struct rule_data * , struct spi_members *);
#endif /* SPI_H */


