#include "tcp_chksum.h"
#include "../../packets/tcp.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool tcp_check_sum_passed(struct __tcp * tcp_hdr, int size){
  uint16_t sent_checksum = tcp_hdr->check;
  
  uint16_t calc_cksum = 0;
  struct __tcp temp_tcp = *tcp_hdr;
  memset(temp_tcp.check,0,sizeof(temp_tcp.check));
  const uint16_t * raw_chk = (const uint16_t*)&temp_tcp;

  while(size > 1){
    calc_cksum += *raw_chk++;
    size -= sizeof(uint16_t);
  }
  if(size)
    calc_cksum += *(uint16_t*)raw_chk;

  calc_cksum = (calc_cksum >> 16) + (calc_cksum & 0xffff);
  calc_cksum += (calc_cksum >> 16);
  printf("%02x --- %02x\n",raw_chk,calc_cksum);
  if(sent_checksum != calc_cksum){
    return false;
  }
  return true;
}   