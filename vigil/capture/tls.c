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


#include "nethdr/tlsdata.h"
#include "decode/tls.h"
#include "engine/rule/rule.h"
#include <pcap.h>
#include "globals.h"

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
