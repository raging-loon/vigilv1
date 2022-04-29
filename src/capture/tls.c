#include "../packets/tlsdata.h"
#include "tls.h"
#include "../filter/parsing/rule.h"
#include <pcap.h>

void tls_decode(const unsigned char * pkt ,struct rule_data * rdata,const struct pcap_pkthdr * pkt_hdr){
  struct tlsd * __tlsdata = (struct tlsd *)(pkt);
  switch(__tlsdata->content_type){
    case 0x14:
      // change cipher spec
      break;
    case 0x16:
      tls_handshake(pkt,rdata,pkt_hdr);
      break;
    case 0x17:
      // application data
      break;
    default:
      // suspicious packet
      break;
  }
}

void tlshandshake(const unsigned char * pkt,struct rule_data * rdata,const struct pcap_pkthdr * pkt_hdr){
  struct tls_handshake * tlsh = (struct tls_handshake *)(pkt + sizeof(struct tlsd));
  
}
