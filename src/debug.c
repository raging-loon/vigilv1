#include "debug.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "../globals.h"

void livedebug( const char * msg,...){
  if(debug_mode){
    char debug_msg[256];
    va_list args;
    va_start(args,msg);
    sprintf(debug_msg,msg,args);
    printf("%s\n",debug_msg);
    va_end(args);
  }
}
