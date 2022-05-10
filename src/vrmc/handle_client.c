#include "vrmc.h"
#include "opcodes.h"
#include <stdbool.h>
#include <sys/socket.h>
#include "../../globals.h"
#include <arpa/inet.h>

void handle_client(void * cptr){
  connect_t * cnx = (connect_t*)cptr;
  unsigned int stage = STAGE_VERSION;
  
  while(true){
    if(stage == STAGE_VERSION){
      version_exchange(cnx);
    }
  }
  close(cnx->fd);
}


void version_exchange(connect_t * cnx){
  send(cnx->fd,VERSION,strlen(VERSION),0);

  char buffer[1024];
  int len_read = read(cnx->fd,buffer,1024);
  if(len_read <= 0){
    close(cnx->fd);
  } else{

    return;
  }
}