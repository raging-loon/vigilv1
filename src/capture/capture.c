#include "capture.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>
#include "pktmgr.h"
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

void init_pcap_int(struct vpcap * vpkt,char * iface){
  if((vpkt->fd = socket(AF_INET,SOCK_RAW,IPPROTO_RAW)) < 0){
    perror("Failed to open raw socket");
    exit(EXIT_FAILURE);
  }
  const int len = strnlen(vpkt->interface,IF_NAMESIZE);
  // if(setsockopt(vpkt->fd,SOL_SOCKET,))
}
void start_pcap_loop(struct vpcap *);

