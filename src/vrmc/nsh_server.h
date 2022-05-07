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

#ifndef NSH_SERVER_H
#define NSH_SERVER_H
#include <sys/socket.h>
#include <stdbool.h>
#define NSH_RPC_PORT            641

typedef struct{
  int file_desc;
  struct sockaddr_in * __socket;
  char sym_key[1024];
} connect_t;

void start_nsh_server();

// thread
static void actually_start_nsh_server();
static void accept_cmd(void *);
// static bool nsh_do_login(int,const char *);
#endif /* NSH_SERVER_H */ 