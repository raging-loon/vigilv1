#ifndef ARP_HDR
#define ARP_HDR

struct arp_hdr{
  unsigned int hw_type:             16;
  unsigned int proto_type:          16;
  unsigned int hwlen:               8;
  unsigned int protoln:             8;
  unsigned int opcode:              16;
  unsigned char src_mac[6];
  unsigned char src_ip[4];
  unsigned char dst_mac[6];
  unsigned char dst_ip[4];
};

#endif /* ARP_HDR */