#include "monitoring.h"
#include <stdio.h>
#include <stdlib.h>

static int get_line_num(FILE * fp){
  int num_lines = 0;
  char ch;
  while((ch = fgetc(fp)) != EOF){
    if(ch == '\n') num_lines++;
  }
  return num_lines;
}
