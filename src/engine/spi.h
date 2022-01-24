#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "../statistics/watchlist.h"
#include "../statistics/wldataset.h"
#include "../filter/parsing/rule.h"


const enum{
  LISTENING = 240,
  ESTABLISHED,
  FINISHED

} spi_status_t;



struct spi_tcp_table{
  
  char * server_addr[18];
  char * client_addr[18];
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
  int status;
  unsigned int start_time;
  
};



int conversation_exists(const struct rule_data *);


void add_pkt_data(const struct spi_tcp_table *);


void * spi_scan();
#endif /* SPI_H */


