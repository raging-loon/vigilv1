#include "vrmc.h"
#include "opcodes.h"
#include <stdbool.h>
#include <sys/socket.h>
// #include <base64.h>
#include "../../globals.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
static __thread char buffer[1024];

#define CLEAR_BUFFER memset(&buffer,0,sizeof(buffer));


void handle_client(void * cptr){
  connect_t * cnx = (connect_t*)cptr;
  unsigned int stage = STAGE_VERSION;
  
  while(true){
    if(stage == STAGE_VERSION){
      version_exchange(cnx);
      stage = STAGE_KEX;
    } 
    else if(stage == STAGE_KEX){
      vkex(cnx);
      stage = STAGE_KEX;
    }

  }
  close(cnx->fd);
}


void version_exchange(connect_t * cnx){
  CLEAR_BUFFER
  send(cnx->fd,VERSION,strlen(VERSION),0);

  int len_read = read(cnx->fd,buffer,1024);
  if(len_read <= 0){
    close(cnx->fd);
  } else{

    return;
  }
}

void vkex(connect_t * cnx){
  CLEAR_BUFFER
  send(cnx->fd,pubkey,pubkey_len,0);
  int len_read = read(cnx->fd,buffer,1024);
  if(len_read <= 0){
    close(cnx->fd);
  } else if(!(strncmp(pubkey,buffer,len_read) == 0)){
    close(cnx->fd);
  } else {
    return;
  }

}