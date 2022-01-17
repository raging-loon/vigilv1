#include <stdint.h>
#include "spi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"
#include "../debug.h"

void add_pkt_data(const struct pkt_spi * pdata){
  if(spi_max <= spi_pkt_now){  
   livedebug("spi.c: add_pkt_data: spi_pkt_now = %d",spi_pkt_now);
    for(int i = 0; i < spi_max; i++){
      
    }    
    
    spi_pkt_now = 0;
    // return;
  }
}


