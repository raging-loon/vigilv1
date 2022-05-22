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
  if((vpkt->fd = socket(PF_INET,SOCK_RAW,IPPROTO_RAW)) == -1){
    perror("Failed to open raw socket");
    exit(EXIT_FAILURE);
  }
  const int len = strnlen(vpkt->interface,IF_NAMESIZE);
  setsockopt(vpkt->fd,SOL_SOCKET,25,vpkt->interface,len);

}
void start_pcap_loop(struct vpcap * vi){
  pthread_t vi_thread;
  pthread_create(&vi_thread,NULL,&__start_pcap_loop,vi);
}

void __start_pcap_loop(void * args){
  struct vpcap * vi = (struct vpcap *)args;
  vi->tid = pthread_self(); // get tid
  size_t addr_len = sizeof(vi->sock);
  

}

