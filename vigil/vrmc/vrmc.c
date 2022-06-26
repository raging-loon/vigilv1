/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/
#include "vrmc.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include "../globals.h"
#include <netdb.h>
#include <sys/types.h>
#include "base64.h"
#include <unistd.h>
#include "../utils.h"

unsigned char * pubkey;
unsigned char * privkey;
int pubkey_len;
int privkey_len;

void read_pub_key(){
  pubkey = (unsigned char *)malloc(1024);
  memset(&pubkey,0,sizeof(pubkey));
  char temp_pubkey[1024] = {0};

  
  FILE * f_pubkey = fopen("/etc/vigil/keys/pubkey.crt","r");
  size_t pos,len;
  char * line = NULL;

  while((pos = getline(&line,&len,f_pubkey)) != -1){
    if(strloc(line,'-') != -1) continue;
    line[strcspn(line,"\n")] = 0;
    strcat(&temp_pubkey,line);
  }
  pubkey = base64_decode(temp_pubkey,strlen(temp_pubkey));
  pubkey_len = strlen(temp_pubkey) / 4 * 3;
  // printf("%02x",pubkey);
  fclose(f_pubkey);

}

void read_private_key(){
  privkey = (unsigned char *)malloc(2048);
  memset(&privkey,0,sizeof(privkey));
  char temp_privkey[2048] = {0};
  FILE * f_privkey = fopen("/etc/vigil/keys/privkey.pem","r");
  char * line = NULL;
  size_t pos, len;
  while((pos = getline(&line,&len,f_privkey)) != -1){
    if(strloc(line,'-') != -1) continue;
    line[strcspn(line,"\n")] = 0;
    strcat(&temp_privkey,line);
  }
  privkey = base64_decode(temp_privkey,strlen(temp_privkey));
  privkey_len = strlen(temp_privkey) / 4 * 3;
  fclose(f_privkey);
}
void free_keys(){
  free(pubkey);
  free(privkey);
}

void start_vrmc_server(){
  read_pub_key();
  read_private_key();
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

  if(listen(fd,2) < 0){
    perror("vrmc.c: listen");
    exit(EXIT_FAILURE);  
  }

  while(true){
    int csock;
    if((csock = accept(fd,(struct sockaddr*)&addr,(socklen_t *)&addrlen)) < 0){
      printf("Failed to accept client at %s\n",get_formated_time());

    } else {

      connect_t cnct_ptr;
      cnct_ptr.fd = csock;
      pthread_t client_thread;
      pthread_create(&client_thread,NULL,&handle_client,&cnct_ptr);
      // pthread_join(&client_thread,NULL);
    }
  }

}