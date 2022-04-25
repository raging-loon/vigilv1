#ifndef BACKTRACE_H
#define BACKTRACE_H
#define TOTAL_FN            256

typedef struct{
  char fn_name[32];
  char mem_loc[16];
} fn_mem_loc;
extern fn_mem_loc fn_mem_map[TOTAL_FN];
extern int fn_num;
void load_fn_mem_map();
void add_fn(void * fn, char * fn_name);
void print_mem_map();
void crash_handler(int );


#endif /* BACKTRACE_H */