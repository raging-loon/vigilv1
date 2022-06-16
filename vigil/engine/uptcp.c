
#include "spi.h"
#include "../filter/parsing/rule.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void tcp_syn_handler(struct spi_members * sm){
  if(sm->status == __SPI_UNINIT)
    sm->status = __TCP_INIT;
  
  printf("SPI loc:%d New TCP Conversation: 1/3 3WH %s:%d -> %s:%d\n",
          sm->location, sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
  fflush(stdout);
}

void tcp_syn_ack_handler(struct spi_members * sm){
  printf("%d:here\n",sm->location);
  if(sm->status == __TCP_INIT){
    sm->status = __TCP_ACK_W;
     printf("SPI TCP Conversation: 2/3 3WH %s:%d -> %s:%d\n",
          sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
    fflush(stdout); 
  }
}
void tcp_rst_handler(struct spi_members * sm);
void tcp_ack_handler(struct spi_members * sm);
void tcp_rst_ack_handler(struct spi_members * sm);
void tcp_fin_handler(struct spi_members * sm);
void tcp_fin_ack_handler(struct spi_members * sm);