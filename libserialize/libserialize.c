#include "libserialize.h"
#include <stdio.h>
#include <string.h>
#ifndef LIBTEST
# include "../src/engine/spi.h"
#endif

unsigned char * sm_to_bytes(struct spi_members * sm){
  return (unsigned char *)sm;
}
// unsigned char * sm_to_php(struct spi_members *);

#ifdef lIBTEST
// 140.82.112.3|10.108.32.227|443|50800|12|20|20|12|126|0|1649171618|1649171661|16|15

int main(int argc, char ** argv){
  struct spi_members sm;
  strcpy(sm.serv_addr, "140.82.112.3");
  strcpy(sm.cli_addr,"10.108.32.227");
  sm.serv_port = 443;
  sm.dest_port = 50800;
  sm.serv_packet_sent = 12;
  sm.cli_packet_sent = 20;
  sm.serv_packet_recv = 20;
  sm.cli_packet_rec = 12;
  sm.protocol = 126; // R_TCP
  sm.pps = 0;
  sm.start_time = 1649171618;
  sm.end_time = 1649171661;
  sm.control_pkts = 15;
  sm.data_pkts = 16;
  
  printf("%s\n",sm_to_bytes(&sm));

}

#endif