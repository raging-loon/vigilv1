#ifndef CAPTURE_H
#define CAPTURE_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
struct vpcap{
  // int mode;
  char * interface;
  int fd;
  struct sockaddr_in sock;
  int mode;
  pthread_t tid;
};

void init_pcap_int(struct vpcap *, char *);
void start_pcap_loop(struct vpcap *);
void __start_pcap_loop(void *);

#endif /* CAPTURE_H */