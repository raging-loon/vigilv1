#ifndef ETH_HDR_H
#define ETH_HDR_H
#include <inttypes.h>
struct eth_hdr{
  uint8_t h_dest[6];
  uint8_t h_source[6];
  uint16_t h_proto;
};

#endif /* ETH_HDR_H */