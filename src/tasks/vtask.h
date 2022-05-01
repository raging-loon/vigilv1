#ifndef __VTASK_H
#define __VTASK_H
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#define MAX_TASKS     256

extern vtask tasks[MAX_TASKS]; 

#define VT_CONDITION_NEW_LOGON_VIA_UNENCRYPTED_API            32
#define VT_CONDITION_RULE_POSITIVE                            33
#define VT_CONDITION_PROGRAM_START                            34
#define VT_CONDITION_PROGRAM_END                              35



typedef struct {
  unsigned int type;
  bool (*condition_chk)();
  void (*task)();
  uint32_t conditions;
  
} vtask;



void add_new_task();

void vts_listen();

void vt_scan_tasks();







#endif /* __VTASK_H */