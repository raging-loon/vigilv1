
#include "spi.h"
#include "../filter/parsing/rule.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum tcp_flags get_tcp_flags(struct rule_data * rdata){
  // URG should always come last
  if(strncmp(rdata->tcp_flags,"AFPRSU", 6) == 0){
    return TCP_ALL;
  }
  else if(strlen(rdata->tcp_flags) == 0){
    return TCP_NONE;
  }
  // get rid of URG flag
  rdata->tcp_flags[strcspn(rdata->tcp_flags,"U")] = '\0';


  
}

void tcp_syn_handler(struct spi_members * sm);

void tcp_syn_ack_handler(struct spi_members * sm);
void tcp_rst_handler(struct spi_members * sm);
void tcp_ack_handler(struct spi_members * sm);
void tcp_rst_ack_handler(struct spi_members * sm);
void tcp_fin_handler(struct spi_members * sm);
void tcp_fin_ack_handler(struct spi_members * sm);