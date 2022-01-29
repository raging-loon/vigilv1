#ifndef __SPI_H
#define __SPI_H



#include "../filter/parsing/rule.h"
#include "engine.h"

const enum{
  __TCP_LISTENING = 240,
  __TCP_ESTABLISHED, /* ACK */ 
  __TCP_FINISHED,
  __TCP_INIT,  /* SYN */
  __TCP_ACK_W, /* SYN/ACK */
  __TCP_FIN_INIT,
  __TCP_FIN_INIT2,
  __TCP_RST_COMP,
  __TCP_RST_INIT,
  __TCP_RST_INIT2,
  __TCP_CLOSED_FIN,
  __TCP_CLOSED_RST,
  __UDP_FIRST_SEEN,
  __ICMP_FIRST_SEEN,


} spi_status_t;



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
};


typedef struct{
  int table_location;
  int direction;
#define DIR_CLIENT_TO_SERVER        100
#define DIR_SERVER_TO_CLIENT        101
} spi_info;



spi_info conversation_exists(struct rule_data *);

void add_new_conversation(struct rule_data *);

void update_table(struct rule_data *);
// void add_pkt_data(const struct spi_tcp_table *);
void spi_ud_thw(struct rule_data *);

void update_information(struct spi_members *, spi_info *);
void table_roll_over();
void end_connection(struct rule_data *);
void * spi_scan();
#endif /* SPI_H */


