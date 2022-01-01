#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../../globals.h"
#include "update_db.h"
void * update_arp_cache(void * args){
  update_db_t * update = args;
  
  
  MYSQL connection; 
  
  mysql_init(&connection);
  if(!mysql_real_connect(&connection, "localhost", 
                         &mysql_user,&mysql_password,"NPSIDB",3306, NULL, 0)){
    //
    printf("ERROR COULD NOT CONNECT TO MYSQL SERVER: %s\n",mysql_error(&connection));
    goto close;
  }
  // printf("%s\n",connection.passwd);

  char query[512];
  switch(update->update_type){
    case ARP_UP_T:
      sprintf(query,"INSERT INTO arp_cache (ip_address, mac_address) VALUES (\"%s\", \"%s\");",update->ip_addr,update->mac);
      break;
    case STAT_UP_T:
      if(update->is_new){
        sprintf(query,"");
      }
  }
  // printf("%s\n",query);
  int status = mysql_query(&connection,query);
  if(status){
    printf("Failed to query\n");
  }
close:
  mysql_close(&connection);
}