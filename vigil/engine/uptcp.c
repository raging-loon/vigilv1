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
#include "spi.h"
#include "../filter/parsing/rule.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void tcp_syn_handler(struct spi_members * sm){
  if(sm->status == __SPI_UNINIT)
    sm->status = __TCP_INIT;
  
  printf("SPI loc:%d New TCP Conversation: 1/3 3WH %s:%d -> %s:%d\n",
          sm->location, sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
  fflush(stdout);
}

void tcp_syn_ack_handler(struct spi_members * sm){
  if(sm == NULL){
    return;
  }
  
  if(sm->status == __TCP_INIT){
    printf("SPI TCP Conversation: 2/3 3WH %d %s:%d -> %s:%d\n",
          sm->location, sm->cli_addr,sm->cli_port,sm->serv_addr,sm->serv_port);
    fflush(stdout); 
    sm->status = __TCP_ACK_W;
  }
}
void tcp_ack_handler(struct spi_members * sm){
  if(sm == NULL) {
    return;
  }

  if(sm->status == __TCP_ACK_W){
    printf("SPI TCP Conversation 3WH complete: %d %s:%d -> %s:%d\n", 
    sm->location,sm->cli_addr, sm->cli_port, sm->serv_addr, sm->serv_port);
    fflush(stdout);
    sm->status = __TCP_ESTABLISHED;
  } else if(sm->status == __TCP_FIN_INIT2){
    printf("SPI TCP Conversation closed: %d %s:%d -> %s:%d\n", 
    sm->location,sm->cli_addr, sm->cli_port, sm->serv_addr, sm->serv_port);
    fflush(stdout);
    sm->conversation_active = false;
  }
}


void tcp_rst_handler(struct spi_members * sm){
  if(sm == NULL){
    printf("sm == null\n");
    return;
  }
  if(sm->status == __TCP_ACK_W){
    printf("Possible syn scan detected %s:%d -> %s:%d\n",sm->cli_addr,sm->cli_port,sm->serv_addr, sm->serv_port);
    fflush(stdout);
    sm->conversation_active = false;
  }
}

void tcp_rst_ack_handler(struct spi_members * sm){
  if(sm == NULL){
    fflush(stdout);
    return;
  }
  if(sm->status == __TCP_INIT){
    printf("Interaction with closed port: %s:%d -> %s:%d\n",sm->cli_addr,sm->cli_port,sm->serv_addr, sm->serv_port);
    fflush(stdout);
    sm->conversation_active = false;
  }
}
void tcp_fin_handler(struct spi_members * sm);

void tcp_fin_ack_handler(struct spi_members * sm){
  if(sm->status == __TCP_ESTABLISHED){
      printf("SPI TCP Conversation FIN END 1/3 %d %s:%d -> %s:%d\n", 
      sm->location,sm->cli_addr, sm->cli_port, sm->serv_addr, sm->serv_port);
      sm->status = __TCP_FIN_INIT;
  } else if(sm->status == __TCP_FIN_INIT){
      printf("SPI TCP Conversation FIN END 2/3 %d %s:%d -> %s:%d\n", 
      sm->location,sm->serv_addr, sm->serv_port, sm->cli_addr, sm->cli_port);
      sm->status = __TCP_FIN_INIT2;
  }
}