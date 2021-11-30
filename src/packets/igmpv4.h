#ifndef IGMP_V4_H
#define IGMP_V4_H
#include <stdint.h>

struct main_igmp{
  uint8_t type;
}

struct igmpv4_member_qry{
  uint8_t type;
  uint8_t max_resp_time;
  uint16_t checksum;
  uint32_t multicast_address;
  uint8_t flags;
  uint8_t QQIC;
  uint16_t num_src;
};

struct igmp_member_report{
  uint8_t type;
  uint8_t reserved;
  uint16_t checksum;
  uint16_t reserved2;
  uint16_t number_group_records;
  uint8_t record_type;
  uint8_t aux_data_len;
  uint16_t num_len;
  uint32_t multicast_address;
};
#endif /* IGMP_V4_H */