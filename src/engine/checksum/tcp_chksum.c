#include "tcp_chksum.h"
#include "../../packets/tcp.h"
#include <stdbool.h>


bool tcp_check_sum_passed(struct __tcp * tcp_hdr, int size){
  uint16_t sent_checksum = tcp_hdr->check;
  uint16_t calc_cksum = 0;
  const unsigned int * raw_chk = (const unsigned int*)tcp_hdr;

  while(size > 1){
    calc_cksum += *raw_chk++;
    size -= sizeof(uint16_t);
  }
  if(size)
    calc_cksum += *(uint16_t*)raw_chk;

  calc_cksum = (calc_cksum >> 16) + (calc_cksum & 0xffff);
  calc_cksum += (calc_cksum >> 16);
  if(sent_checksum != calc_cksum){
    return false;
  }
  return true;
}   