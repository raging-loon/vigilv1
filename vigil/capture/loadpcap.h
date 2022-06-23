#ifndef LOAD_PCAP_H
#define LOAD_PCAP_H
// #define PRE_RELEASE_TEST
#ifdef PRE_RELEASE_TEST

#include <inttypes.h>
extern int time_type;

#define TIME_TYPE_MS        0x01
#define TIME_TYPE_NS        0x02
typedef struct {
  uint32_t ts_seconds;
  uint32_t ts_var_sec;
  uint32_t cap_len;
  uint32_t var_len;
} lpacket;

struct pcap_filehdr{
  uint32_t magic;
  uint16_t mjr_version;
  uint16_t mnr_version;
  uint32_t res1;
  uint32_t res2;
  uint32_t snaplen;
  unsigned int fcs:       3;
  unsigned int fbit:      1;
  unsigned int linktype:  28;
};

void loadpcap(const char *);

#endif


#endif /* LOAD_PCAP_H */