#include "loadpcap.h"
#include "pktmgr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef PRE_RELEASE_TEST
int time_type;
static void print_sum_end(const char * sum){
  for(int i = 0; i < strlen(sum); i++){
    printf("-");
  }
  printf("\n");
}

void loadpcap(const char * filename){
  struct pcap_filehdr file_header;
  FILE * fp = fopen(filename,"rb");
  if(fp == NULL){
    printf("Failed to load pcap file: %s",filename);
    exit(-1);
  }
  char start_sum[39 + strlen(filename)];
  sprintf(start_sum,"--------[ PCAP SUMMARY ]--------\n");
  printf("%s",start_sum);
  printf("Filename: %s\n",filename);
  fread(&file_header,sizeof(file_header),1,fp);
  if(file_header.magic == 0xa1b2c3d4){
    printf("Timestamp: microsecond\n");
    time_type = TIME_TYPE_MS;
  } 
  else if(file_header.magic == 0xa1b23cd4){
    printf("Timestamp: nanosecond\n");
    time_type = TIME_TYPE_NS;
  }
  else {
    printf("Unknown timestamp, exiting...\n");
    print_sum_end(start_sum);
    exit(EXIT_FAILURE);
  }
  printf("Version: %d.%d\n",file_header.mjr_version,file_header.mnr_version);
  printf("Snaplen: %d\n",file_header.snaplen);
  print_sum_end(start_sum);

  while(1){
    lpacket temp;
    fread(&temp,sizeof(temp),1, fp);
    unsigned char pkt_data[2048];
    memset(&pkt_data,0,sizeof(pkt_data));
    fread((char *)&pkt_data,temp.cap_len,1, fp);
    pktmgr(temp.cap_len,pkt_data);
    if(feof(fp)) break; 
  }
  fclose(fp);
}

#endif