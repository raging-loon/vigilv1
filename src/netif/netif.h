#ifndef NET_IF_H
#define NET_IF_H
#include <pthread.h>
#include <stdbool.h>



typedef struct{
  char if_name[17];
  // pthread_t * thrd_id;
  unsigned long thrd_id;
  bool active;
  unsigned int a_family;
  char address[100];
  // unsigned int function;
} v_netif;

extern v_netif * net_interfaces;


// void start_interface_cap();
void detect_interfaces();
void free_iface();
#endif /* NET_IF_H */