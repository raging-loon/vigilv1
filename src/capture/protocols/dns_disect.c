#include "../../filter/parsing/rule.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../packets/dns.h"
#include "dns_disect.h"
#include "../../utils.h"
void dns_disect(const unsigned char * pkt, const struct rule_data * rdata){
  struct dns_pkt_data * dns_data = (struct dns_pkt_data*)(pkt);
  char * query = pkt + sizeof(struct dns_pkt_data);
  printf("%s\n",get_dns_name(query));
}

char * get_dns_name(const char * qry){
  char * real_qry = "";

  for(int i = 0; qry[i] != 0x00; i++){
      printf("sdsdf\n");
    if(!IS_PRINTABLE_ASCII(qry[i])) continue;
    if(qry[i] == 0x03 || qry[i] == 0x06){
      strcat(real_qry,".");
    } else {
      strcat(real_qry,(char *)&qry[i]);
    }
  }
  return real_qry;
}
