#include "vrmc.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

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

   

}