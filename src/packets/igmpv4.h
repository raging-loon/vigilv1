#ifndef IGMP_V4_H
#define IGMP_V4_H
#include <stdint.h>

struct __igmpv4{
  uint8_t type;
  uint8_t max_resp_time;
  uint16_t checksum;
  
};


#endif /* IGMP_V4_H */