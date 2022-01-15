#include <stdint.h>
#include "spi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../globals.h"


void add_pkt_data(const struct pkt_spi * pdata){
  if(spi_max <= spi_pkt_now){  
   
   
   
   
    spi_pkt_now = 0;
  }
}


