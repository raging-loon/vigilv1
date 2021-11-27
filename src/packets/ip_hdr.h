#ifndef __IP_HDR_H
#define __IP_HDR_H
// this struct only exists for detecting fragmented packets
#include <stdint.h>
struct ip_hdr{
  uint8_t version;
  uint8_t tos;
  uint16_t tot_len;
  uint16_t id;
  uint16_t flags;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t hdr_chksum;
  uint32_t saddr;
  uint32_t daddr;
};



#endif /* __IP_HDR_H */
