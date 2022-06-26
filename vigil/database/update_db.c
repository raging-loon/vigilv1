/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/

#include <stdio.h>
#include <stdlib.h>
#include "../globals.h"
#include <sqlite3.h>
#include "update_db.h"
#include "../engine/spi.h"

/*
  *-*-*-*- update_db.c -*-*-*-*
  @purpose Update the SQLite database located where specified in the config file.
  void * update_db(void * args);
    ==> This function is designed to only be run on another thread.
    Please note that there are not functions for each type of update, that is 
    so there aren't a bunch of update_db_t structs.
    Instead, this is organsized and relatively fast.

    @TODO: Add SQL statements for other tables.   
*/



void * update_db(void * args){
  update_db_t * update = (update_db_t*)args;
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
  return (void *)1; 
}


void * update_spi_db(void * spi_data){
  sqlite3 * db;
  struct spi_members * sm = (struct spi_members*)spi_data;
  if(sqlite3_open("/usr/share/vigil/spi.db",&db)){
    printf("SQLite error %s\n",sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }
  char statement[1024];
  char * b_statement = "INSERT INTO spi_table ("
                            "serv_addr, cli_addr,serv_port,cli_port,"
                            "serv_pkt_sent,cli_pkt_sent,serv_pkt_recv,cli_pkt_recv,"
                            "protocol,avg_pps,start_time,end_time,data_pkts,control_pkts) "
                            "VALUES (\"%s\",\"%s\",%ld,%ld,%d,%d,%d,%d,%d,%d,%ld,%ld,%d,%d);";
  sprintf(statement,b_statement,
          sm->serv_addr,sm->cli_addr,
          sm->serv_port,sm->cli_port,
          sm->serv_packet_sent,*sm->cli_packet_sent,
          sm->serv_packet_recv,*sm->cli_packet_recv,
          sm->protocol,sm->pps,sm->start_time,sm->end_time,
          sm->data_pkt,sm->control_pkt);
  char * errmsg = 0;
  if(sqlite3_exec(db,statement,0,0,&errmsg) != SQLITE_OK){
    printf("SQLITE Encountered error: %s\n",errmsg);
  }
  return NULL;
}