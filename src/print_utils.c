#include <stdio.h>
#include "print_utils.h"


void ascii_hexdump(unsigned char * pkt_bytes, int datalen){
  for(int i = 0; i < datalen; i++){
    if(pkt_bytes[i] > 32 && pkt_bytes[i] < 127)
      printf("%c",pkt_bytes[i]);
    else
      printf(".");
  }
  printf("\n");
}