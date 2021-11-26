#ifndef IP6_HDR_H
#define IP6_HDR_H
#include <stdint.h>
struct ip6hdr{
  // unsigned int version:             8;
  unsigned int misc_info:           32;
  unsigned int payload_len:         16;
  unsigned int n_hdr:               8;
  unsigned int hop_limit:           8;
  uint8_t srcaddr[16];
  
  uint8_t dstaddr[16];            
};

#endif /* IP6_HDR_H */