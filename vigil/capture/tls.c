/*
 * Copyright 2021-2022 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */


#include "../packets/tlsdata.h"
#include "tls.h"
#include "../filter/parsing/rule.h"
#include <pcap.h>
#include "../globals.h"

void tls_decode(const unsigned char * pkt ,struct rule_data * rdata,const int len){
  struct tlsd * __tlsdata = (struct tlsd *)(pkt);
  // printf("0x%02x\n",__tlsdata->content_type);
  switch(__tlsdata->version){
    case 0x0301:
      if(packet_print) printf("TLS 1.0 DATA: ");
      rdata->encrypted = true;    
      break;
    case 0x0302:
      if(packet_print) printf("TLS 1.2 DATA: ");
      rdata->encrypted = true;
      break;
    case 0x0303:
      if(packet_print) printf("TLS 1.3 DATA: ");
      rdata->encrypted = true;
      break;
    default:
      return;
  }

  switch(__tlsdata->content_type){
    case 0x14:
      // change cipher spec
      break;
    case 0x15:
      // alert
      break;
    case 0x16:
      tlshandshake(pkt,rdata,len);
      break;
    case 0x17:
      // application data
      break;
    default:
      // suspicious packet
      break;
  }
}

void tlshandshake(const unsigned char * pkt,struct rule_data * rdata,const int len){
  struct tls_handshake * tlsh = (struct tls_handshake *)(pkt + sizeof(struct tlsd));
  // printf("0x%02x\n",tlsh->handshake_type);
  switch(tlsh->handshake_type){
    case 0x01:
      // if(packet_print) 
      printf("Client Hello\n");
      rdata->encrypted = true;
      break;
    case 0x02:
      if(packet_print) printf("Server Hello\n");
      rdata->encrypted = true;
      break;
    case 0x04:
      if(packet_print) printf("New Session Ticket\n");
      rdata->encrypted = true;
      break;    
    case 0x0b:
      if(packet_print) printf("Certificate\n");
      rdata->encrypted = true;
      break;

    case 10:
      if(packet_print) printf("Client Kex\n");
      rdata->encrypted = true;
      break;
    
    
  }
}
