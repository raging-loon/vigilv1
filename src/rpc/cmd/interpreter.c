#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "interpreter.h"
#include "helpmsgs.h"
#include "nsh_commands.h"
#include "../../../globals.h"
void nsh_cmd_interpret(const char * input, int fd){
  // rnstrip(input);
  if(strcmp(input,"test_echo") == 0){
    send(fd,"hello\r\n",7,0);
  } 
  else if(strncmp(input,"exit",4) == 0){
    
    return;
  }
  else if(strncmp(input,"get",3) == 0){
    
    if(strlen(input) < 3){
      send(fd,get_cmd_help,strlen(get_cmd_help),0);
      return;
    }
    else if(strncmp(input + 4,"blacklist",9) == 0){
      send_blacklist(&fd);
      return;
    } 
    else if(strcmp(input + 4, "rules") == 0){
      get_loaded_rules(&fd);
      return;
    }
    else if(strncmp(input + 4,"matches",8) == 0){
      get_rule_matches(&fd,input + 12);
      return;
    }
    else if(strncmp(input + 4, "packets",8) == 0){
      char message[32];
      sprintf(message,"Total packets caught: %d\r\n",total_pkt_captured);
      send(fd,message,strlen(message),0);
    return;
    }
    else if(strncmp(input + 4, "arp",3) == 0){
      get_arp_cache(&fd);
      return;
    }
    else{
      send(fd,get_cmd_help,strlen(get_cmd_help),0);
    }
  }


  else if(strncmp(input,"add",3) == 0){
    if(strlen(input) < 4){
      send(fd,add_cmd_help,strlen(add_cmd_help),0);
    }
    else if(strncmp(input + 4,"blacklist",9) == 0){
      add_to_blacklist(&fd,input + 4);
    }
    else if(strncmp(input + 4,"rule",4) ==0){
      load_new_rule(&fd, input + 8);
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