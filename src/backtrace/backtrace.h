#ifndef BACKTRACE_H
#define BACKTRACE_H

typedef struct{
  char fn_name[32];
  unsigned int mem_loc;
} fn_io_map;

void load_fn_io_map();
#endif /* BACKTRACE_H */