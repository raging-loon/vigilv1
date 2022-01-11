#include <stdio.h>
#include "watchlist.h"
#include "wclean.h"
#include <stdlib.h>
#include <string.h>
#include "../../globals.h"
#include <time.h>
#include <pthread.h>
int ready_for_clean(const struct watchlist_member * w){
  if((time(NULL) - w->last_time_seen) >= clean_delay){
    // printf("%s\n",w->ip_addr);
    return 1;
  } 
  else return -1;
}

void clean(struct watchlist_member * w){
  memset(w,0,sizeof(w));
  strcpy(w->ip_addr,"0.0.0.1");
}

void scan_for_clean(){
  // printf("Scanning for clean\n");
  for(int i = 0; i < watchlist_num + 1; i++){
    if(ready_for_clean(&watchlist[i]) > 0) clean(&watchlist[i]);
  }
}

