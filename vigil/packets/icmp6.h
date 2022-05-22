#ifndef ICMP6_H
#define ICMP6_H
#include <stdint.h>
struct __icmp6{
  uint8_t icmp_type;
  uint8_t icmp_code;
  uint16_t icmp_check_sum;
  uint32_t icmp_reserved;
  uint8_t icmp_src_lyr_type;
  uint8_t icmp_src_lyr_len;
  uint8_t addr[6];
};


#endif /* ICMP6_H */