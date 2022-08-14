/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/

#include "../engine/checksum/tcp_chksum.h"

#include "../config/rule.h"
#include "protocols/http_disect.h"
#include "protocols/ftp-disect.h"
#include "../packets/ip_hdr.h"
#include "../engine/flags.h"
#include "../print_utils.h"
#include "../packets/tcp.h"
#include "../globals.h"
#include "../engine/spi.h"
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "protocols.h"
#include "../colors.h"
#include "../utils.h"
#include "../debug.h"
#include <stdbool.h>
#include <stdint.h>
#include "tcpmgr.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "tls.h"

/*
  *-*-*-*- tcpmgr.c -*-*-*-*
  @purpose Provide decoding for TCP 
    ==> Decode the TCP header in IPv4 Packets
    Data decoded:
      - Ports
      - Flags
      - TOS 
      - TTL 
    In this function, rst and fin port scans will be detected. If either of these flags are set,
    a series of instructions will figure out if the destination IP(rst) or the src(fin) should fo through the 
    tcp_rst_portscan_detect or the fin_rst_portscan_detect functions located in /src/statistics/watchlist.c

    Various part of the TCP and IP header are added to the rdata(struct rule_data) structure so rules can be 
    adequately applied via the rulemgr function(/src/filter/parsing/rule.c)
  @TODO: add support for IPv6(URGENT)
*/

void ip4_tcp_decode(const unsigned char * pkt,struct rule_data * rdata,const int len){
  // int * p  = 0; *p = 0; // this crashes the program. only use this to test the backtrace functions

  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr));
  
  
  rdata->pkt = (unsigned char *)(pkt + ETH_HDR_SZ +  sizeof(struct ip_hdr) + (tcp_hdr->doff * 4));
  

  
  rdata->pkt_len = rdata->pkt_len - ETH_HDR_SZ - sizeof(struct ip_hdr) - (tcp_hdr->doff * 4);
  const char * src_ip = rdata->src_ip_addr;
  const char * dest_ip = rdata->dest_ip_addr;
  // add_ip_addr_or_inc_counter(src_ip,true,TCP);
  // add_ip_addr_or_inc_counter(dest_ip,false, TCP);
  unsigned int dest_port,  src_port;
  int flags_set = 0;
  // bool rst_set = false; // possible future use
  bool ack_set = false;
  bool syn_set = false;
  bool fin_set = false;
  bool psh_set = false;
  memset(&rdata->tcp_flags,0,sizeof(rdata->tcp_flags));
  // uint16_t syn, ack, rst, fin, psh, urg;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
  rdata->dest_port = (unsigned int )ntohs(tcp_hdr->dest);

  rdata->src_port = src_port;
  if(packet_print){
    printf("%s",__TCP_COLOR_NS);
    printf("IPv4 %s:%d -> %s:%d\n",
                    src_ip, src_port, dest_ip, dest_port);
    printf("\tTCP [");
  // printf("[");
  

  } 
  if((uint16_t)ntohs(tcp_hdr->urg) != 0){
    if(packet_print) printf("%s URG ",__TCP_URG);
    flags_set++;
    strcat((char *)&rdata->tcp_flags,"U");
  } 
  
  if((uint16_t)ntohs(tcp_hdr->syn) != 0){
    if(packet_print) printf("%s SYN ", __TCP_SYN);
    syn_set = true;
    strcat((char *)&rdata->tcp_flags,"S");
    flags_set++;
  }
   if((uint16_t)ntohs(tcp_hdr->rst) != 0){
    if(packet_print) printf("%s RST ",__TCP_RST);
    // rst_set = true;
    strcat((char *)&rdata->tcp_flags,"R");
    flags_set++;
  }
  if((uint16_t)ntohs(tcp_hdr->psh) != 0){
    if(packet_print) printf("%s PSH ",__TCP_PSH);
    flags_set++;
    strcat((char *)&rdata->tcp_flags,"P");
    psh_set = true;
  }
  // AFPRSU
  if((uint16_t)ntohs(tcp_hdr->fin) != 0){
    if(packet_print) printf("%s FIN ",__TCP_FIN);
    fin_set = true;
    strcat((char *)&rdata->tcp_flags,"F");
    flags_set++;
  }

  if((uint16_t)ntohs(tcp_hdr->ack) != 0){
    if(packet_print) printf("%s ACK ",__TCP_ACK);
    ack_set = true;
    strcat((char *)&rdata->tcp_flags,"A");
    flags_set++;
  }  

  if(packet_print) {
    printf("%s",__TCP_COLOR_NS);
    // printf(" %s ", rdata->fla);
    printf("]\n");
    printf("%s",__END_COLOR_STREAM);
  }
  /*
  if(tcp_check_sum_passed(rdata->ip_header,tcp_hdr)){
    printf("Checksum passed\n");
  } else {
    printf("Invalid checksum\n");
  }*/
  if(flags_set > 3 || flags_set == 0){
    printf("%sSuspicious TCP Packet encoutered: %s:%d -> %s:%d, %d flags%s\n",
    __TCP_RST, 
    src_ip,
    src_port,
    dest_ip,
    dest_port,
    flags_set,
    __END_COLOR_STREAM);
  }

  if(use_spi){
    spi_handler(rdata);
  }
  
  if(PSH_ACK_SET(psh_set,ack_set) && flags_set == 2) rdata->is_established = true;


  
  if(packet_print){
    if((PSH_ACK_SET(psh_set,ack_set) && !fin_set) && IS_PORT_DEST_SRC(dest_port,src_port,80)){
      http_disect(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr) + sizeof(struct __tcp) + 12,rdata);
    }
  }
  if((IS_PORT_DEST_SRC(dest_port,src_port,443)) && PSH_ACK_SET(psh_set,ack_set)){
    tls_decode(rdata->pkt,rdata,len);
  }
  // if(packet_print)
  // ascii_hexdump(pkt + ETH_HDR_SZ + sizeof(struct ip_hdr) + (tcp_hdr->doff * 4),
                // ->len - ETH_HDR_SZ - sizeof(struct ip_hdr) - (tcp_hdr->doff * 4));
  rdata->dsize = len - ETH_HDR_SZ - sizeof(struct ip_hdr) - (tcp_hdr->doff * 4);
  
  rulemgr(rdata);
}
