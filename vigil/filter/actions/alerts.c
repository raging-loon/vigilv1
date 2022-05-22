#include <stdio.h>
#include <stdlib.h>
#include "alerts.h"
#include "../../globals.h"
#include "../../print_utils.h"
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
/*
  *-*-*-*- alerts.c -*-*-*-*
  @purpose Alert administrators of events
  @TODO: Add support for the following:
    - rsyslog
    - SNMP
    - Monitoring systems
    - Email
  
*/
void format_msg(const struct rule_data* rdata, const struct rule * r, char * restrict buf){
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
  if(rdata->__protocol == R_ICMP){
    sprintf(buf,"%s %s %s -> %s\n", time, r->message, rdata->src_ip_addr, rdata->dest_ip_addr);
  } else {

    sprintf(buf,"%s %s %s:%d -> %s:%d\n",time, r->message,
	  													rdata->src_ip_addr,
	  													rdata->src_port,
	  													rdata->dest_ip_addr,
	  													rdata->dest_port);
  }
        
}


void stdout_alert(const struct rule_data* __rule_data, const struct rule * __rule, int a_level){
  char message[256];
  format_msg(__rule_data, __rule, (char*)&message);
  printf("%s",message);
//   ascii_hexdump(__rule_data->pkt,__rule_data->pkt_len);
}

void ipc_msg_alrt(const struct rule_data * rdata, const struct rule * r, int a_level){
  ipc_queue_mem mesg;
  format_msg(rdata, r, (char*)&mesg.data);
  key_t key;
  key = ftok("progfile",65);
  // printf("%d\n",key);
  int msgid = msgget(key, 0666 | IPC_CREAT);
  mesg.type = 1;
  // mesg.pid = getppid();
  msgsnd(msgid,&mesg,sizeof(mesg),0);
}

void log_alert(const struct rule_data* rdata, const struct rule* r, int a_level){
  char message[256];
  format_msg(rdata,r,(char *)&message);
  FILE * fp = fopen(def_log_file,"a");
  fputs(message,fp);
  fclose(fp);
}
