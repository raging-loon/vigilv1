#include "../../packets/igmpv4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../protocols.h"
#include <netinet/ip.h>

void ip4_igmp_decode(const unsigned char * pkt, const char * src_ip, const char * dest_ip){
  struct main_igmp * type_decode = (struct main_igmp *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));
  printf("IPv4 IGMP %s -> %s [", src_ip ,dest_ip);
  switch(main_igmp->type){
    case 0x22:{
      printf(" Membership Query ]\n");
      break;
    }
  } 
}

