#include "vrmc.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include "../../globals.h"
#include "../utils.h"

void start_vrmc_server(){
  pthread_t vthrd;
  pthread_create(&vthrd,NULL,&__start_vrmc_server,NULL);

}

void __start_vrmc_server(){
  int fd, sock, input;

  struct sockaddr_in addr;
  int addrlen = sizeof(addr);

  if((fd = socket(AF_INET,SOCK_STREAM, 0)) == 0){
    perror("vrmc: failed to create socket");
    exit(EXIT_FAILURE);
  }

  if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR, &addrlen,sizeof(addrlen))){
    perror("vrmc.c: failed setsockopt");
    exit(EXIT_FAILURE);
  }
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(641);

  if(bind(fd, (struct sockaddr*)&addr,sizeof(addr)) < 0){
    perror("vrmc.c: failed socket binding");
    exit(EXIT_FAILURE);
  }

  if(listen(fd,5) < 0){
    perror("vrmc.c: listen");
    exit(EXIT_FAILURE);  
  }

  while(true){
    int csock;
    if((csock = accept(fd,(struct sockaddr*)&addr,(socklen_t *)&addrlen)) < 0){
      printf("Failed to accept client at %s\n",get_formated_time());

    } else {

      connect_t cnct_ptr;
      cnct_ptr.fd = fd;
      pthread_t client_thread;
      pthread_create(&client_thread,NULL,&handle_client,&cnct_ptr);
      // pthread_join(&client_thread,NULL);
    }
  }

}

void handle_client(void * cptr){
  connect_t * cnx = (connect_t*)cptr;
  unsigned int stage = 0;
  version_exchange(cnx);
  
  while(true){
    //
  }
  close(cnx->fd);
}

void version_exchange(connect_t * cnx){
  send(cnx->fd,VERSION,strlen(VERSION),0);
  printf("Here\n");
  char buffer[1024];
  int len_read = read(cnx->fd,buffer,1024);
  if(len_read <= 0){
    close(cnx->fd);
  } else{
    // check 
    return;
  }
  close(cnx->fd);
}