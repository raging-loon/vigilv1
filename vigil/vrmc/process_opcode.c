/*
 * Copyright 2021-2022 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "vrmc.h"
#include "vrmc.h"
#include "opcodes.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../globals.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static __thread char buffer[1024];

void process_opcode(connect_t * cnx){
  while(true){
    int len_read = read(cnx->fd,buffer,1024);
    if(len_read <= 0) break;
    
  }
}