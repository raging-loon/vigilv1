
#include "spi.h"
#include "../filter/parsing/rule.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void tcp_syn_handler(struct spi_members * sm){
  printf("SPI New TCP Conversation: 1/3 %s:%d -> %s:%d\n",
          sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
  fflush(stdout);
}

void tcp_syn_ack_handler(struct spi_members * sm);
void tcp_rst_handler(struct spi_members * sm);
void tcp_ack_handler(struct spi_members * sm);
void tcp_rst_ack_handler(struct spi_members * sm);
void tcp_fin_handler(struct spi_members * sm);
void tcp_fin_ack_handler(struct spi_members * sm);