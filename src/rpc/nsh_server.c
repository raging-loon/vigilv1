#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "nsh_server.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

void start_nsh_server(){
		// fork();
    pthread_t pthrd;
    pthread_create(&pthrd,NULL,&actually_start_nsh_server,NULL);
    // pthread_join(pthrd,NULL);
}



static void *actually_start_nsh_server(){
	// fork();
  int nsh_fd, sock, input;
  struct sockaddr_in addr;
  int addrlen = sizeof(addr);
  if((nsh_fd = socket(AF_INET, SOCK_STREAM,0)) == 0){
    printf("nsh_server.c: failed to create socket\n");
    exit(EXIT_FAILURE);
  }
	if(setsockopt(nsh_fd,SOL_SOCKET,SO_REUSEADDR , &addrlen,sizeof(addrlen))){
		printf("nsh_server.c: failure in setsockopt\n");
		exit(EXIT_FAILURE);
	}
	char * lb = "127.0.0.1";
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	// strcpy(&addr.sin_addr.s_addr,NSH_LOOPBACK);
	addr.sin_port = htons(NSH_RPC_PORT);


	if(bind(nsh_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		printf("nsh_server.c: binding of socket for nsh_fd failed\n");
		exit(EXIT_FAILURE);
	}
	
	if(listen(nsh_fd,5) < 0){
		printf("nsh_server.c: failure on listening for nsh_fd\n");
		exit(EXIT_FAILURE);
	}
	
	
	while(true){
		
		int client_sock;
		if((client_sock = accept(nsh_fd, (struct sockaddr *)&addr,(socklen_t *)&addrlen)) <0){
			time_t t = time(NULL);
  		struct tm __time = *localtime(&t);
  		char time[64];
  		sprintf(time,"%d-%02d-%02d %02d:%02d:%02d",
  		        __time.tm_year + 1900,
  		        __time.tm_mon + 1,
  		        __time.tm_mday,
  		        __time.tm_hour,
  		        __time.tm_min,
  		        __time.tm_sec);
			printf("Failure to accept a client at %s\n",time);

		} else {
			
			printf("new connection at %s\n",inet_ntoa(addr.sin_addr));
		}
	}

}
