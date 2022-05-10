#ifndef CAPTURE_H
#define CAPTURE_H

struct vpcap{
  // int mode;
  char * interface;
  int fd;
};

void init_pcap_int(struct vpcap *, char *);
void start_pcap_loop(struct vpcap *);


#endif /* CAPTURE_H */