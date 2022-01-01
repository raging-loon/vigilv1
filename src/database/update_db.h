#ifndef UDPATE_DB_H
#define UDPATE_DB_H
#include "../statistics/watchlist.h"
#include "../statistics/ip_addr_stat.h"
typedef struct {
  char ip_addr[16];
  char mac_addr[18];
  int update_type;
  struct watchlist_member w;
  struct ip_addr_counter ip_stat;
  int is_new;
} update_db_t;

const enum{
  ARP_UP_T,
  STAT_UP_T,
  WATCH_UP_T
} udb_type_t;

void * update_db(void *);


#endif /* UDPATE_DB_H */