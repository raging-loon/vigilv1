#ifndef LIBSERIALIZE_H
#define LIBSERIALIZE_H

#ifndef LIBTEST
# include "../src/engine/spi.h"
#endif
/*
  data structure -> raw bytes -> modular serialization -> output
  
  Please note that these functions only apply to the data structure in the Vigil IDS,
  they will not work an any other data structure.
*/
#ifdef LIBTEST
#include <stdbool.h>
struct spi_members{
  unsigned char * serv_addr;
  unsigned char * cli_addr;
  unsigned int serv_port;
  unsigned int cli_port;
  int serv_packet_sent;
  int serv_packet_recv;
  // the following pointers are pointers to the two above, 
  // they only exist to make this easier to write.
  int * cli_packet_sent; 
  int * cli_packet_recv; 

  unsigned int data_pkt, control_pkt;

  int num_cli_rules;
  int num_srv_rules;
  unsigned int status;
  unsigned long start_time;
  unsigned long end_time;
  unsigned int total_packets;
  unsigned int protocol;
  unsigned int pps; /* Packets per second */
  int possible_retransmissions;
  bool conversation_active;
};

int main(int argc, char ** argv);
#endif
unsigned char * sm_to_bytes(struct spi_members *);
unsigned char * sm_to_php(struct spi_members *);
// unsigned char * sm_to_pypickle(struct spi_members *);
// unsigned char * sm_to_java(struct spi_members *);



#endif /* LIBSERIALIZE_H */