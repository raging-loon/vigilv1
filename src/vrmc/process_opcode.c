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

#include "nsh_server.h"
#include "vrmc.h"
#include "opcodes.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../../globals.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// static __thread char buffer[1024];
void process_opcode(struct vrmc_ops * ops, connect_t * c){
  char buffer[1024];
  switch(ops->opcode){
    case VOPCODE_GET_VERSION:{ 
      struct v_info{
        unsigned int opcode: 8;
        unsigned int version: 24;
      };
      struct v_info v = {VOPCODE_GET_VERSION, VERSION_NUM};
      unsigned char* bytes = (unsigned char *)&v;
      send(c->file_desc,bytes,4,0);
      break;
    }
  }
}