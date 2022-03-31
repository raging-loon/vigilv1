#ifndef __SPI_H
#define __SPI_H



#include "../filter/parsing/rule.h"
#include "engine.h"


#define __TCP_LISTENING       240
#define  __TCP_ESTABLISHED    241 
#define  __TCP_FINISHED       242      
#define  __TCP_INIT           243
#define  __TCP_ACK_W          244
#define  __TCP_FIN_INIT       245
#define  __TCP_FIN_INIT2      246
#define  __TCP_RST_COMP       247
#define  __TCP_RST_INIT       248
#define  __TCP_RST_INIT2      249
#define  __TCP_CLOSED_FIN     250
#define  __TCP_CLOSED_RST     251
#define  __UDP_FIRST_SEEN     252
#define  __ICMP_FIRST_SEEN    253



struct spi_members{
  struct net_addr server_addr;
  struct net_addr client_addr;
  unsigned int serv_port;
  unsigned int cli_port;
  int serv_packet_sent;
  int serv_packet_recv;
  // the following pointers are pointers to the two above, 
  // they only exist to make this easier to write.
  int * cli_packet_sent; 
  int * cli_packet_recv; 


  struct rule * srv_rules[32];
  struct rule * cli_rules[32];
  int num_cli_rules;
  int num_srv_rules;
  unsigned int status;
  unsigned long start_time;
  unsigned long end_time;
  unsigned int total_packets;
  unsigned int pps; 
  unsigned int protocol;
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

void update_table(struct rule_data *);
// void add_pkt_data(const struct spi_tcp_table *);
void spi_ud_thw(struct rule_data *);

void update_information(struct spi_members *, spi_info *);
void table_roll_over();
void end_connection(struct rule_data *);
void * spi_scan();
#endif /* SPI_H */


