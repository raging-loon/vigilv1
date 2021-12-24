#include "nsh_commands.h"
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../globals.h"
#include "../../filter/parsing/rule_parser.h"
void send_blacklist(int fd){
  char blacklist_msg[1024]; //= "Blacklist for nsh server:\n\t";
  strcat(blacklist_msg,"Blacklist for nsh server:\n\t");
  for(int i = 0; i < blk_ipv4_len + 1; i++){
    const char * ipv4_addr = (const char *)&blocked_ipv4_addrs[i].ipv4_addr;
    strncat(blacklist_msg,ipv4_addr,strlen(ipv4_addr));
    // printf("got here\n");
    strcat(blacklist_msg,"\n\t");
  }
  strcat(blacklist_msg,"\r\n");
  send(fd,blacklist_msg,strlen(blacklist_msg),0);
}

void add_to_blacklist(int fd, const char * ro_cmd){
  if(strncmp(ro_cmd + 10,"ipv4",4) == 0){
    const char *ipv4_addr = ro_cmd + 15;
    char success_msg[32];
    struct blocked_ipv4 * temp = &blocked_ipv4_addrs[++blk_ipv4_len];
    strcpy(temp->ipv4_addr,ipv4_addr);
    sprintf(success_msg,"Added %s to blacklist\r\n",ipv4_addr);
    send(fd,success_msg,strlen(success_msg),0);
  }
}

void get_loaded_rules(int fd){
  char message[1024];
  strcat(message,"Loaded rules for NPSI Server:\n\t");
  for(int i = 0; i < num_rules + 1; ){
    const struct rule * tmprule = &rules[i++];
    strncat(message,tmprule->rulename,strlen(tmprule->rulename));
    strcat(message,"\n\t");
  }
  strcat(message,"\r\n");
  send(fd,message,strlen(message),0);
}

void load_new_rule(int fd,const char * cmd){
  FILE * fp = fopen(cmd + 1,"r");
  char message[64];
  if(fp == NULL){
    sprintf(message,"Failure to open file %s\r\n",cmd);
    send(fd,message,strlen(message),0);
    return;
  }
  rule_parser(cmd);
  sprintf(message,"Loaded rule file %s\r\n",cmd);
  send(fd,message,strlen(message),0);
}