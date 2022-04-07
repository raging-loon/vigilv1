#include "vwebsrv.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdbool.h>
void start_web_server(){
  pthread_t pthrd;
  pthread_create(&pthread_atfork,NULL,&start_web_server_thrd,NULL);
}
void * start_web_server_thrd(){
  int srv_fd, sock, input;
  struct sockaddr_in addr;
  int addrlen = sizeof(addr);
  if((srv_fd = socket(AF_INET,SOCK_STREAM,0)) == 0){
    printf("web/vwebsrv.c: failed to create socket\n");
    exit(EXIT_FAILURE);
  }
  if(setsockopt(srv_fd,SOL_SOCKET,SO_REUSEADDR, &addrlen,sizeof(addrlen))){
    printf("web/vwebsrv.c: failure in setsockopt\n");
    exit(EXIT_FAILURE);
  }
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(443);
  if(bind(srv_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    printf("VWEBSRV: failed to bind\n");
    exit(EXIT_FAILURE);
  }
  if(listen(srv_fd,5) < 0){
    printf("VWEBSRV: failed to listen\n");
    exit(EXIT_FAILURE);
  }
  while(true){
    int client_sock;
    // if((client_sock = accept(srv_fd, ())))
  }
}



#ifdef FUNCTIONALITY_TEST


int main(int argc, char ** argv){
  printf("Hello\n");
}


#endif