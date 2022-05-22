#ifndef __TCP_H_
#define __TCP_H_
#include <stdint.h>
#include <bits/endian.h>
struct __tcp{
  uint16_t source;
  uint16_t dest;
  uint32_t seq;
  uint32_t ack_seq;
#if __BYTE_ORDER == __LITTLE_ENDIAN
  uint16_t  res1: 4;
  uint16_t  doff: 4;
  uint16_t  fin:  1;
  uint16_t  syn:  1;
  uint16_t  rst:  1;
  uint16_t  psh:  1;
  uint16_t  ack:  1;
  uint16_t  urg:  1;
  uint16_t  ece:  1;
  uint16_t  cwr:  1;
           
#elif defined(__BIG_ENDIAN__)
  uint16_t doff: 4;
  uint16_t res1: 4;
  uint16_t cwr:  1;
  uint16_t ece:  1;
  uint16_t urg:  1;
  uint16_t ack:  1;
  uint16_t psh:  1;
  uint16_t rst:  1;
  uint16_t syn:  1;
  uint16_t fin:  1;
#else
#   error "Fix <bits/endian.h>"
#endif
  uint16_t window;
  uint16_t check;
  uint16_t urg_ptr;
} __attribute__((packed));
#endif /* __TCP_H_ */