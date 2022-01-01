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
  if(dns_data->flags == 0){
    char real_query[64];
    memset(&real_query,0,sizeof(real_query));
    get_dns_name(query,&real_query);

    printf("%s\n",real_query);
  }
}

void get_dns_name(const char * qry, char * output){
  
  for(int i = 0; i < strlen(qry); i++){
    
      if(qry[i] > 32)strncat(output,&qry[i],1);
      else strcat(output,".");
    
  }
}
