#ifndef VRMC_H
#define VRMC_H
#include <stdint.h>

struct vrmc_ops{
  uint8_t opcode;
};

typedef struct{
  int fd;
  char sym_key[1024];
} connect_t;

void start_vrmc_server();
void __start_vrmc_server();

/**************** VRMC Protocol ****************

  client -> three way handshake -> server
 
  client -> send version
 
  server -> send version
  server: check version, in future version there will be a list of 
          unsupported version
  server -> send public key
  client -> recv public key and store
  server -> send randomly generated AES key
  client -> ack and store
  server -> store

  client -> switch to AES key 
  
  client -> send ready to recv opcode
  server -> send ready to recv opcode

  client -> send login opcode with logon information
  server -> check info
  server -> if info is correct, issue uuid cookie
  client -> ack that uuid cookie was recieved and send it back
  server -> check uuid cookie
  server -> send authenticated opcode
  
  if client was not correctly authenticated, server will send opcode saying so nd terminate the connection

*/
#define EX_STAGE_VERSION    0x01
void version_exchange(connect_t *);
void handle_client(void *);

#endif /* VRMC_H */