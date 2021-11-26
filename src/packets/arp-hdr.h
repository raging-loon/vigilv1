#ifndef ARP_HDR
#define ARP_HDR
#include <stdint.h>
struct arp_hdr{
  // unsigned int hw_type:             16;
  // unsigned int proto_type:          16;
  // unsigned int hwlen:               8;
  // unsigned int protoln:             8;
  // unsigned int opcode:              16;
  // unsigned char src_mac[6];
  // unsigned char src_ip[4];
  // unsigned char dst_mac[6];
  // unsigned char dst_ip[4];
  // unsigned char runoff[4];
  uint16_t      hw_type;
  uint16_t      proto_type;
  uint8_t       hw_len;
  uint8_t       protoln;
  uint16_t      opcode;
  uint8_t       src_mac[6];
  uint32_t      src_ip;
  uint8_t       dst_mac[6];
  uint32_t      dst_ip;
};

#endif /* ARP_HDR */