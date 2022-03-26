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
#include "debug.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "../globals.h"

void livedebug( const char * msg,...){
  if(debug_mode){
    // char debug_msg[256];
    va_list args;
    va_start(args,msg);
    printf(msg,args);
    // printf("%s\n",debug_msg);
    va_end(args);
  }
}
