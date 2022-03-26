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
#include <stdio.h>
#include <stdarg.h>
#include "logging.h"
#include "utils.h"
#include "../globals.h"

void lprintf(FILE * fp, const char * fmt, ...){
  va_list args;
  va_start(args,fmt);
  fprintf(fp,fmt, args);
  va_end(args);
}


void lfprintf(const char * filename, const char * msg, const char * src, const char * dest, int sport, int dport){
  FILE * fp = fopen(filename,"a");
  if(fp == NULL){
    printf("CRITICAL FAILED TO OPEN FILE FOR LOGGING: %s\n",msg);
    return;
  }

  char message[2048];
  char time[64];
  cb_get_formatted_time(time);
  if(sport == -1){
    sprintf(message,"%s %s %s -> %s\n",time,msg,src,dest);
  } else {
    sprintf(message,"%s %s %s:%d -> %s:%d\n",time,msg,src,sport,dest,dport);
  }
  fputs(message,fp);
  fclose(fp);
}
void saprintf(const char * msg){
  FILE * fp = fopen(def_log_file,"a");
  if(fp == NULL){
    printf("CRITICAL FAILED TO OPEN FILE FOR LOGGING: %s\n",msg);
    return;
  }
  fputs(msg,fp);
  fclose(fp);
}
