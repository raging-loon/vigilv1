#ifndef ICMP4_H
#define ICMP4_H
#include <stdint.h>
struct __icmp4{
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
  uint16_t id;
  uint16_t seq;
  uint8_t timestamp[8];
  uint8_t data[128];
};

#endif /* ICMP4_H */