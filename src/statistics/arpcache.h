#ifndef ARP_CACHE_H
#define ARP_CACHE_H
#include <stdint.h>

struct arp_entry{
  uint8_t ip_addr[4];
  uint8_t mac_addr[6];
};



void compare_entries(uint8_t , uint8_t );
void add_entry(uint8_t *, uint8_t *);
int entry_exists(uint8_t,uint8_t);
int compare_ip_entry(uint8_t *,uint8_t *);
int compare_mac_entry(uint8_t *,uint8_t * );

#endif /* ARP_CACHE_H */ 