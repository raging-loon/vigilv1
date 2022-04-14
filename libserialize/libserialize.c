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

  sprintf(php_ser_buff,"O:11:\"spi_members\":14:{"
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

void sm_to_pypickle(struct spi_members * sm, unsigned char * py_pickle_buf){
  /*
    """
    (b'\x80\x04\x95#\x01\x00\x00\x00\x00\x00\x00\x8c\x11vigil.classes.spi\x94\x8c'
    b'\x0bspi_members\x94\x93\x94)\x81\x94}\x94(\x8c\tserv_addr\x94\x8c\x0b192.1'
    b'68.0.1\x94\x8c\x08cli_addr\x94\x8c\x0b192.168.0.2\x94\x8c\tserv_port\x94'
    b'M\xbb\x01\x8c\x08cli_port\x94M\x99\xdc\x8c\x10serv_packet_sent\x94'
    b'K\x0c\x8c\x0fcli_packet_sent\x94K\x14\x8c\x0fcli_packet_recv\x94'
    b'K\x0c\x8c\x10serv_packet_recv\x94K\x14\x8c\x08protocol\x94K~\x8c\x03pp'
    b's\x94K\x00\x8c\nstart_time\x94J\xa2\\Lb\x8c\x08end_time\x94J\xcd\\Lb\x8c\x0b'
    b'control_pkt\x94K\x0f\x8c\x08data_pkt\x94K\x10ub.')
    """
  */

  sprintf(py_pickle_buf,"%c",0x80);
}




// #ifdef lIBTEST
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
  sm_to_pypickle(&sm,(unsigned char*)&php_data);
  printf("%s\n",php_data);
}

// #endif