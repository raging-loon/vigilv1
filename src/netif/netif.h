#ifndef NET_IF_H
#define NET_IF_H
#include <pthread.h>
#include <stdbool.h>
struct v_net_if{
  char if_name[17];
  // pthread_t * thrd_id;
  unsigned long thrd_id;
  bool active;
  // unsigned int function;
};

void start_interface_cap();

#endif /* NET_IF_H */