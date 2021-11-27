#include "tcpmgr.h"
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include "protocols.h"
#include "../packets/tcp.h"
void ip4_tcp_decode(const unsigned char * pkt){
  struct __tcp * tcp_hdr = (struct __tcp *)(pkt + ETH_HDR_SZ + sizeof(struct iphdr));
  unsigned int dest_port,  src_port;
  dest_port = (unsigned int)ntohs(tcp_hdr->dest);
  src_port = (unsigned int)ntohs(tcp_hdr->source);
   
}
