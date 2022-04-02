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

#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H
#include "l_run_condition.h"
#define MAX_LUA_SCRIPTS             20 // for now
struct l_script{
  char filename[64];
  struct l_run_condition conditions;
};

extern struct l_script lua_scripts[MAX_LUA_SCRIPTS];

void collect_scripts();


void run_hello_script();

#endif /* LUA_ENGINE_H */