#ifndef __DNS_H
#define __DNS_H
#include <stdint.h>


struct dns_pkt_data{
  uint16_t transaction_id;
  uint16_t flags;
  uint16_t questions;
  uint16_t ans_rr;
  uint16_t auth_rr;
  uint16_t additional_rr;
  
};
#endif /* __DNS_H */