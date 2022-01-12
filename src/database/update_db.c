#include <stdio.h>
#include <stdlib.h>
#include "../../globals.h"
#include <sqlite3.h>
#include "update_db.h"

static int callback(void *unused, int argc, char **argv, char **colname){
  return 0 ;
}
void * update_db(void * args){
  update_db_t * update = args;
  printf("Updating db\n");
  char * err = 0;
  sqlite3* database; 
  int status = sqlite3_open(sqlite_db_path,&database);
  if(status){
    printf("SQlite error: %s\n",sqlite3_errmsg(database));
    goto close;
  } 
  char query[512];
  
  switch(update->update_type){
    case ARP_UP_T:
      sprintf(query,"INSERT INTO arp_cache (ip_address, mac_address) VALUES (\"%s\", \"%s\");",update->ip_addr,update->mac_addr);
      break;
  }
  status = sqlite3_exec(database,query,NULL,NULL,&err);
  if(status != SQLITE_OK){
    printf("SQLite encountered error: %s\n",err);
    sqlite3_free(err);
  }
 close: 
  sqlite3_close(database);
}