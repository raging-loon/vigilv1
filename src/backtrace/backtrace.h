#ifndef BACKTRACE_H
#define BACKTRACE_H
#define TOTAL_FN            256
extern fn_mem_loc fn_mem_map[TOTAL_FN];
extern int fn_num;
typedef struct{
  char fn_name[32];
  char mem_loc[16];
} fn_mem_loc;

void load_fn_mem_map();
void add_fn(void * fn, char * fn_name);
void crash_handler(int );


#endif /* BACKTRACE_H */