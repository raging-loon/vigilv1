#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
char * mac_ntoa(uint8_t );
char * ipv4_ntoa( uint32_t *);
unsigned char * inet6_ntoa(uint8_t * );
#endif /* UTILS_H */