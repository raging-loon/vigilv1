#include <stdio.h>
#include "watchlist.h"
#include "wclean.h"
#include <stdlib.h>
#include <string.h>
#include "../../globals.h"
#include <time.h>
#include <pthread.h>
int ready_for_clean(const struct watchlist_member * w){
  if(w->last_time_seen >= clean_delay) return 1;
  else return -1;
}

void clean(struct watchlist_member * w){
  memset(w,0,sizeof(w));
  strcpy(w->ip_addr,"0.0.0.1");
}

void scan_for_clean(){
  printf("Scanning for clean\n");
  for(int i = 0; i < watchlist_num + 1; i++){
    if(ready_for_clean(&watchlist[i]) > 0) clean(&watchlist[i]);
  }
}


inline void is_ready_for_clean(){
  if((unsigned long)time(NULL) - last_clean_time >= clean_delay) scan_for_clean();
}


void * clean_wait(){
  printf("Running clean scheduler\n");
  while(1){
    if(is_running == 0)return;
    
    for(int i = 0; i < 100; i++){}
    is_ready_for_clean();
  }
}


void start_wclean(){
  pthread_t pthrd;
  pthread_create(&pthrd,NULL,&clean_wait,NULL);
}