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
#include <stdbool.h>


#define __TCP_LISTENING       240
#define  __TCP_ESTABLISHED    241 /* ACK - end of twh*/
#define  __TCP_FINISHED       242      
#define  __TCP_INIT           243 /* SYN */
#define  __TCP_ACK_W          244 /* SYN/ACK */
#define  __TCP_FIN_INIT       245 /* FIN/ACK */
#define  __TCP_FIN_INIT2      246 /* FIN/ACK */
#define  __TCP_RST_COMP       247
#define  __TCP_RST_INIT       248
#define  __TCP_RST_INIT2      249
#define  __TCP_CLOSED_FIN     250
#define  __TCP_CLOSED_RST     251
#define  __UDP_FIRST_SEEN     252
#define  __ICMP_FIRST_SEEN    253
#define  __TCP_FIN_END        254 /* ACK */

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
  bool session_encrypted;
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

extern unsigned int total_conversations;

extern struct spi_members spi_table[1024];


typedef struct{
  int table_location;
  int direction;
#define DIR_CLIENT_TO_SERVER        100
#define DIR_SERVER_TO_CLIENT        101
} spi_info;


void spi_handler(struct rule_data *);
void tcp_spi_handler(struct rule_data *);
int conversation_exists(struct rule_data *);

#endif /* SPI_H */