#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
char * mac_ntoa(uint8_t * );
char * uc_mac_ntoa(unsigned char *);
char * ipv4_ntoa( uint32_t *);
char * u8_ipv4_ntoa(uint8_t * );
unsigned char * inet6_ntoa(uint8_t * );
#endif /* UTILS_H */