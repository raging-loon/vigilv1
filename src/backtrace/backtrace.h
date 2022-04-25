#ifndef BACKTRACE_H
#define BACKTRACE_H
#define TOTAL_FN            256
extern fn_mem_loc fn_mem_map[TOTAL_FN];

typedef struct{
  char fn_name[32];
  unsigned int mem_loc;
} fn_mem_loc;

void load_fn_io_map();


void crash_handler(int );


#endif /* BACKTRACE_H */