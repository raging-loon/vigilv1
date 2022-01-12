#include <stdio.h>
#include "n_ssh.h"
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
void init_ssh_server(){
  pthread_t pthrd;
  pthread_create;
}

void * start_ssh_server(void * args){
  int ssh_fd,sock, input;
  struct sockaddr_in ssh_addr;
  if((ssh_fd = socket(AF_INET,SOCK_STREAM,0)) == 0){
    printf("n_ssh.c: failed to create socket\n");
    exit(EXIT_FAILURE);
  }
  if(setsockopt(ssh_fd,SOL))
}