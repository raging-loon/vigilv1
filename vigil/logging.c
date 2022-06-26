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
#include <stdarg.h>
#include "logging.h"
#include "utils.h"
#include "globals.h"

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
