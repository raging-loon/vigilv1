#ifndef ARP_CACHE_H
#define ARP_CACHE_H
#include <stdint.h>

struct arp_entry{
  char  ip_addr[16];
  char mac_addr[18];
};


void compare_entries(char *, char *);
void add_entry(char *, char *);
int entry_exists(char *,char *);
int compare_ip_entry(char *,char *);
int compare_mac_entry(char *,char * );

void load_csv_arp_cache();

#endif /* ARP_CACHE_H */ 