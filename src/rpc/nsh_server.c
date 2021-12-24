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
#include "cmd/interpreter.h"
#include <openssl/sha.h>
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
	char * lb = "127.0.0.1";
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
			printf("new connection at %s:%d\n",inet_ntoa(addr.sin_addr),htons(addr.sin_port));
			char buffer[128] = {0};

			if(nsh_do_login(client_sock, inet_ntoa(addr.sin_addr)) == false){
				send(client_sock,"Invalid login\r\n",16,0);
				close(client_sock);
			}
			else {
				char * nsh_str = "nsh# ";
				while(strncmp(buffer,"exit",4) !=0){
					send(client_sock,nsh_str,strlen(nsh_str),0);
					int len_read = read(client_sock,buffer,1024);
					rnstrip(buffer);
					nsh_cmd_interpret(buffer,client_sock);
				}
				close(client_sock);
			}
		}
	}

}

static bool nsh_do_login(int fd,const char * rhost){
	const char * del = ":";
	char username[32];
	char password[32];
	char * passwd_ptr;
	send(fd,"NPSI Login Shell\r\n",19,0);
	send(fd,"Username: ",11,0);
	int len_read = read(fd,username,16);
	send(fd,"Password: ",11,0);
	rnstrip((char *)&username);
	len_read = read(fd,&password,16);
	rnstrip((char *)&password);
	passwd_ptr = &password;
	// printf("%s:%s\n",username,password);
	FILE * fp = fopen("/etc/npsi/passwd","r");
	if(fp == NULL){
		printf("Failed to open password file\n");
		return false;
	}
	char * line = NULL;
	size_t pos, len = 0;
	time_t t = time(NULL);
  struct tm __time = *localtime(&t);
  char nowtime[64];
	
  sprintf(nowtime,"%d-%02d-%02d %02d:%02d:%02d",
          __time.tm_year + 1900,
          __time.tm_mon + 1,
          __time.tm_mday,
          __time.tm_hour,
          __time.tm_min,
          __time.tm_sec);
						
	while((pos = getline(&line,&len,fp)) != -1){
		SHA256_CTX ctx;
		unsigned char real_hash[65];
		char temp_password[65];
		unsigned char temp_username[16];
		unsigned char hash[SHA256_DIGEST_LENGTH];
		memset(&hash,0,sizeof(hash));
		memset(&ctx,0,sizeof(ctx));
		memset(&real_hash,0,sizeof(real_hash));
		
		rnstrip(line);
		char * ptr = strtok(line,del);
		strcpy(temp_username,ptr);
		
		if(strcmp(username,temp_username) != 0){
			continue;
		}

		ptr = strtok(NULL,del);
		strcpy(temp_password,ptr);
		// printf("%s\n",passwd_ptr);
		printf("%s\n",temp_password);
		SHA256_Init(&ctx);
		SHA256_Update(&ctx,passwd_ptr,sizeof(passwd_ptr));
		SHA256_Final((unsigned char *)&hash,&ctx);
		
		for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
			sprintf(real_hash + (i * 2),"%02x",hash[i]);
		}

		printf("%s\n",real_hash);

		if(strncmp(real_hash,temp_password,64) == 0){
			FILE * loginfp = fopen("/var/log/npsi/login.log","a");
			
			char logmessage[128];
			sprintf(logmessage,"Successful login for %s at %s from %s\n",username,nowtime,rhost);
			fputs(logmessage,loginfp);
			fclose(loginfp);
			if(line) free(line);
			fclose(fp);
			return true;
		}
	}
	FILE * loginfp = fopen("/var/log/npsi/login.log","a");
	char logmessage[128];
	sprintf(logmessage,"Failed login for %s at %s from %s\n",username,nowtime,rhost);
	fputs(logmessage,loginfp);
	if(line) free(line);
	fclose(fp);
	fclose(loginfp);
	return false;

}