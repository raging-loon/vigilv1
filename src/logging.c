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
  cb_get_formatted_time(&time);
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
  if(fp == -1){
    printf("CRITICAL FAILED TO OPEN FILE FOR LOGGING: %s\n",msg);
    return;
  }
  fputs(msg,fp);
  fclose(fp);
}
