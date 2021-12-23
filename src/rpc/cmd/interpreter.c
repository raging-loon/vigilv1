#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "interpreter.h"

void nsh_cmd_interpret(const char * input, int fd){
  // rnstrip(input);
  if(strcmp(input,"test_echo") == 0){
    send(fd,"hello\r\n",7,0);
  } 
  else if(strncmp(input,"get ",4) == 0){
    
    if(strlen(input) == 4){
      
      
    }
  
  }


  else {
    int len = 28 + strlen(input);
    // error: command not found: %s\r\n
    char msg[len + 2];
    sprintf(msg,"error: command not found: %s\r\n",input);
    send(fd,msg,len,0);
  }

}