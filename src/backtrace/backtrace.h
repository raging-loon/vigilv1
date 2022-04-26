#ifndef BACKTRACE_H
#define BACKTRACE_H
#define TOTAL_FN            256

typedef struct{
  char fn_name[32];
  unsigned int start;
  unsigned int end;

} fn_mem_loc;
extern fn_mem_loc fn_mem_map[TOTAL_FN];
extern int fn_num;
void load_fn_mem_map();
void add_fn(char * name, unsigned int start, unsigned int end);
void print_mem_map();
void crash_handler(int );


#endif /* BACKTRACE_H */