#include "nsh_commands.h"
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../globals.h"
#include "../../filter/parsing/rule_parser.h"
#include "../../statistics/arpcache.h"
#include "../../utils.h"
static __thread char message_buffer[4096];

void send_blacklist(int * fd){
  memset(&message_buffer,0,sizeof(message_buffer));
  strcat(message_buffer,"Blacklist for nsh server:\n\t");
  for(int i = 0; i < blk_ipv4_len + 1; i++){
    const char * ipv4_addr = (const char *)&blocked_ipv4_addrs[i].ipv4_addr;
    strncat(message_buffer,ipv4_addr,strlen(ipv4_addr));
    // printf("got here\n");
    strcat(message_buffer,"\n\t");
  }
  strcat(message_buffer,"\r\n");
  send(*fd,message_buffer,strlen(message_buffer),0);
}

void add_to_blacklist(int * fd, const char * ro_cmd){
  memset(&message_buffer,0,sizeof(message_buffer));
  if(strncmp(ro_cmd + 10,"ipv4",4) == 0){
    const char *ipv4_addr = ro_cmd + 15;
    char success_msg[32];
    struct blocked_ipv4 * temp = &blocked_ipv4_addrs[++blk_ipv4_len];
    strcpy(temp->ipv4_addr,ipv4_addr);
    sprintf(success_msg,"Added %s to blacklist\r\n",ipv4_addr);
    send(*fd,success_msg,strlen(success_msg),0);
  }
}

void get_loaded_rules(int * fd){
  memset(&message_buffer,0,sizeof(message_buffer));
  strcat(message_buffer,"Loaded rules for NPSI Server:\n\t");
  for(int i = 0; i < num_rules + 1; ){
    const struct rule * tmprule = &rules[i++];
    strncat(message_buffer,tmprule->rulename,strlen(tmprule->rulename));
    char submsg[200];
    sprintf(submsg,"\t\t\t\t\t\t[ %d | %d | %s ]",tmprule->port, tmprule->protocol, tmprule->rule_target);
    strcat(message_buffer,submsg);
    strcat(message_buffer,"\n\t");
  }
  strcat(message_buffer,"\r\n");
  send(*fd,message_buffer,strlen(message_buffer),0);
}

void load_new_rule(int * fd,const char * cmd){
  memset(&message_buffer,0,sizeof(message_buffer));
  FILE * fp = fopen(cmd + 1,"r");
  
  if(fp == NULL){
    sprintf(message_buffer,"Failure to open file %s\r\n",cmd);
    send(*fd,message_buffer,strlen(message_buffer),0);
    return;
  }
  rule_parser(cmd);
  sprintf(message_buffer,"Loaded rule file %s\r\n",cmd);
  send(*fd,message_buffer,strlen(message_buffer),0);
}

void get_rule_matches(int * fd, const char * rulename){
  memset(&message_buffer,0,sizeof(message_buffer));
  if(strlen(rulename) > 2){
    for(int i = 0; i < num_rules + 1; i++){
      if(strcmp(rules[i].rulename,rulename) == 0){
        sprintf(message_buffer,"%s was matched %d times\r\n",rulename,rules[i].times_matched);
        send(*fd,message_buffer,strlen(message_buffer),0);
        return;
      }
    }
    sprintf(message_buffer,"%s: rule not found\r\n",rulename);
    send(*fd,message_buffer,strlen(message_buffer),0);
  } else {
    strcat(message_buffer,"Rules and the number of times they were matched:\n");
    for(int i = 0; i < num_rules + 1; ){
      const struct rule * __rule = &rules[i++];
      char sub_message[256];
      sprintf(sub_message,"\t%s matched %d times\n",__rule->rulename,__rule->times_matched);
      strcat(message_buffer,sub_message);
    }
    strcat(message_buffer,"\r\n");
    send(*fd,message_buffer,strlen(message_buffer),0);
  }
}


void get_arp_cache(int * fd){
  memset(&message_buffer,0,sizeof(message_buffer));
  strcat(message_buffer,"Current ARP cache:");
  for(int i = 0; i < arp_entries + 1; i++){
    char entry_msg[64];
    sprintf(entry_msg,"\n\t%s -> %s",
            arpcache[i].ip_addr,
            arpcache[i].mac_addr);
    strcat(message_buffer,entry_msg);
  }
  strcat(message_buffer,"\r\n");
  send(*fd,message_buffer,strlen(message_buffer),0);
}
