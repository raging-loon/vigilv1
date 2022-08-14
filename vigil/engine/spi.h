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
#ifndef __SPI_H
#define __SPI_H



#include "../config/rule.h"
#include <stdbool.h>


#define  __TCP_LISTENING      240
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
#define  __SPI_UNINIT         255

#define SPI_FLOW_CLIENT_TO_SERVER         0xfe
#define SPI_FLOW_SERVER_TO_CLIENT         0xff


struct spi_members{
  char serv_addr[41];
  char cli_addr[41];
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
  unsigned int initvar;
  int location;
  unsigned int flow;
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


void spi_handler(struct rule_data *);
void tcp_spi_handler(struct rule_data *);
int conversation_exists(struct rule_data *);
struct spi_members * add_new_conversation(struct rule_data * );


/* TCP Data/Functions */

void tcp_syn_handler(struct spi_members *);

void tcp_syn_ack_handler(struct spi_members *);
void tcp_rst_handler(struct spi_members *);
void tcp_ack_handler(struct spi_members *);
void tcp_rst_ack_handler(struct spi_members *);
void tcp_fin_handler(struct spi_members *);
void tcp_fin_ack_handler(struct spi_members *);



#endif /* SPI_H */