#ifndef L_RUN_CONDITION
#define L_RUN_CONDITION


struct l_run_condition{
  unsigned int conditions[10];
}; 

// the conditions are a sort of bytecode for speed


/* opcodes - these only include conditional expressions, no assignments*/
#define LRC_IS_EQUAL      0x01
#define LRC_NOT_EQUAL     0x02

#endif /* L_RUN_CONDITION */ 