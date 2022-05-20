#ifndef UDPATE_DB_H
#define UDPATE_DB_H
typedef struct {
  char ip_addr[16];
  char mac_addr[18];
  int update_type;
  int is_new;
} update_db_t;

#define  ARP_UP_T     0
#define  STAT_UP_T    1
#define  WATCH_UP_T   2

void * update_db(void *);

void * update_spi_db(void * spi_data);

#endif /* UDPATE_DB_H */