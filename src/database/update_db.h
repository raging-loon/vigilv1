#ifndef UDPATE_DB_H
#define UDPATE_DB_H
#include "../statistics/watchlist.h"
#include "../statistics/ip_addr_stat.h"
typedef struct {
  char ip_addr[16];
  char mac_addr[18];
  int update_type;
  struct watchlist_member w;
  int is_new;
} update_db_t;

#define  ARP_UP_T     0
#define  STAT_UP_T    1
#define  WATCH_UP_T   2

void * update_db(void *);


#endif /* UDPATE_DB_H */