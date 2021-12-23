#ifndef __MAIN_NPSI_H
#define __MAIN_NPSI_H
#include <pcap.h>
typedef struct {
  pcap_t * pkap;
} args_t;
int main(int, char **);

void sigint_processor(int);
void * start_pcap_loop(void * );

#endif /* __MAIN_NPSI_H */