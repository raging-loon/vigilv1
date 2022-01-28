#include <stdio.h>
#include <stdarg.h>
#include "logging.h"


void lprintf(FILE * fp, const char * fmt, ...){
  va_list args;
  va_start(args,fmt);
  fprintf(fp,fmt, args);
  va_end(args);
}