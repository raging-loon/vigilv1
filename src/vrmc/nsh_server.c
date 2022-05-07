/*
 * Copyright 2021-2022 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "process_opcode.h"
#include "nsh_server.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <arpa/inet.h>
#include "../utils.h"
#include <string.h>
#include <openssl/sha.h>
#include "vrmc.h"



void start_nsh_server(){
		// fork();
    pthread_t pthrd;
    pthread_create(&pthrd,NULL,&actually_start_nsh_server,NULL);
    // pthread_join(pthrd,NULL);
}

void rnstrip(char * input){
  input[strcspn(input,"\n")] = 0;
  input[strcspn(input,"\r")] = 0;
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
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
							
			printf("Failure to accept a client at %s\n",get_formated_time());

		} else {			
			connect_t connection_ptr;
			connection_ptr.file_desc = client_sock;
			connection_ptr.__socket = &addr;
			pthread_t pthrd;
			pthread_create(&pthrd,NULL,&accept_cmd,&connection_ptr);
		}
	}

}
static void accept_cmd(void * args){
	connect_t * connection = args;
	static __thread char buffer[1024] = {0};
	while(true){
		int len_read = read(connection->file_desc,buffer,1024);
		if(len_read <= 0){
			break;
		} 
		
		struct vrmc_ops * ops = (struct vrmc_ops *)&buffer;
		printf("0x%02x\n",ops->opcode);
		process_opcode(ops,connection);

	}
	
	close(connection->file_desc);

}