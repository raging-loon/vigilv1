#include <stdint.h>
#include "spi.h"
#include "../globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void add_pkt_data(const struct pkt_spi * pdata){
  if(spi_pkt_now == spi_max_pkt){  
    spi_pkt_now = 0;
  }
  // struct pkt_spi * spi_pkt = &last_pkts_spi[spi_pkt_now];
  memset(&last_pkts_spi[spi_pkt_now],0,sizeof(struct pkt_spi));
  memcpy(&last_pkts_spi[spi_pkt_now],pdata,sizeof(pdata));
}


