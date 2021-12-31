#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../../globals.h"
void update_arp_cache(const char * ip, const char * mac){
  MYSQL connection; 
  printf("%s\n",connection.passwd);
  
  mysql_init(&connection);
  printf("trying: %s:%s\n",mysql_user,mysql_password);
  if(!mysql_real_connect(&connection, "localhost", 
                         &mysql_user,&mysql_password,"NPSIDB",3306, NULL, 0)){
    //
    printf("ERROR COULD NOT CONNECT TO MYSQL SERVER: %s\n",mysql_error(&connection));
    goto close;
  }

  char query[110];
  sprintf(query,"INSERT INTO arp_cache ^(ip_address, mac_address) VALUES (%s, %s);",ip_addr,mac);

  int status = mysql_query(&connection,query);
  if(status){
    printf("Failed to query\n");
  }
close:
  mysql_close(&connection);
}