#ifndef VTHRDMGMT_H
#define VTHRDMGMT_H
#include <pthread.h>


typedef struct {
  pthread_t * thrd;
  unsigned long uid;  
  unsigned int fn_id;
} vthread;





#endif /* VTHRDMGMT_H */