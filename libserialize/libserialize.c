#include "libserialize.h"
#include <stdio.h>
#include <string.h>
#ifndef LIBTEST
# include "../src/engine/spi.h"
#endif

unsigned char * sm_to_bytes(struct spi_members * sm){
  unsigned char * buff;
  for(int i = 0; i < sizeof(sm); i++){
    buff[i] = ((unsigned char*)sm)[i];
  }
  return buff;
}
void sm_to_php(struct spi_members * sm, unsigned char * php_ser_buff){
  
  // php object serialization set up like this:
  /*
    <type>:<strlen of obj name>:<objname>:<num members>:{data}
  */

  sprintf(php_ser_buff,"O:11:spi_members:14:{"
                      "s:9:\"serv_addr\";s:%lu:\"%s\";"\
  
                       \
                       "s:8:\"cli_addr\";s:%lu:\"%s\";"\
                       "s:9:\"serv_port\";i:%i;"\
                       "s:8:\"cli_port\";i:%i;"\
                       "s:16:\"serv_packet_sent\";i:%i;"\
                       "s:15:\"cli_packet_sent\";i:%i;"\
                       "s:16:\"serv_packet_recv\";i:%i;"\
                       "s:15:\"cli_packet_recv\";i:%i;"\
                       "s:8:\"protocol\";i:%i;"\
                       "s:3:\"pps\";i:%i;"\
                       "s:10:\"start_time\";i:%lu;"\
                       "s:8:\"end_time\";i:%lu;"\
                       "s:11:\"control_pkt\";i:%i;"\
                       "s:8:\"data_pkt\";i:%i;}", strlen(sm->serv_addr),sm->serv_addr,strlen(sm->cli_addr),sm->cli_addr,
                       sm->serv_port,sm->cli_port,sm->serv_packet_sent,*sm->cli_packet_sent,sm->serv_packet_recv,*sm->cli_packet_recv,
                       sm->protocol,sm->pps,sm->start_time,sm->end_time,sm->control_pkt,sm->data_pkt);
  // printf("%s\n",php_ser_buff);


}

#ifdef lIBTEST
// 140.82.112.3|10.108.32.227|443|50800|12|20|20|12|126|0|1649171618|1649171661|16|15

int main(int argc, char ** argv){
  struct spi_members sm;
  strcpy(sm.serv_addr, "140.82.112.3");
  strcpy(sm.cli_addr,"10.108.32.227");
  sm.serv_port = 443;
  sm.cli_port = 50800;
  sm.serv_packet_sent = 12;
  sm.cli_packet_sent = &sm.serv_packet_recv;
  sm.serv_packet_recv = 20;
  sm.cli_packet_recv = &sm.serv_packet_sent;
  sm.protocol = 126; // R_TCP
  sm.pps = 0;
  sm.start_time = 1649171618;
  sm.end_time = 1649171661;
  sm.control_pkt = 15;
  sm.data_pkt = 16;
  unsigned char php_data[512];
  sm_to_php(&sm,(unsigned char*)&php_data);
  printf("%s\n",php_data);
}

#endif