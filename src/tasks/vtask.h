#ifndef __VTASK_H
#define __VTASK_H
#include <stdint.h>
#include <pthread.h>
#define MAX_TASKS     256

extern vtask tasks[MAX_TASKS]; 

typedef struct {
  unsigned int type;
  void (*task)(struct vtask*);
  uint32_t conditions;
  
} vtask;

typedef struct {
  
} vthreads;


void add_new_task();

void vt_nullify(int); // takes the location of the task in the tasks array






#endif /* __VTASK_H */