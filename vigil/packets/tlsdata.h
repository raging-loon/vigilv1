#ifndef TLSDATA_H
#define TLSDATA_H
#include <stdint.h>
struct tlsd{
  uint8_t content_type;
  unsigned int version: 16;
  uint16_t len;
};

struct tls_handshake{
  uint8_t handshake_type;
  unsigned int length : 24;
  uint16_t version;
  unsigned int random_data[32];
  uint8_t ses_id_len;
  uint16_t cipher_suites_length;
};



#endif /* TLSDATA_H */