#include <stdio.h>
#include "forward.h"
#include "../../config/rule.h"
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ether.h>
#include <string.h>
#include "../../globals.h"
#include "../../print_utils.h"
void forward_packet(const struct rule_data * rdata){
  // unsigned char * raw_packet;
  // if(strcmp(rdata->src_ip_addr,local_ip) != 0 && strcmp(rdata->dest_ip_addr,local_ip) != 0){

  //   strcpy(raw_packet,rdata->pkt + sizeof(struct ethhdr));
  //   ascii_hexdump(raw_packet,rdata->pkt_len - sizeof(struct ethhdr));
  // }
}