#ifndef DPSIZE_H
#define DPSIZE_H
#include "rule.h"


#define D_OP_JE                 0xa1
#define D_OP_JL                 0xa2
#define D_OP_JLE                0xa3
#define D_OP_JG                 0xa4
#define D_OP_JGE                0xa5
#define D_OP_NE                 0xa6

void d_op_parser(struct rule *, const char *, int );

bool d_engine(const struct rule*, const struct rule_data *);


#endif /*DPSIZE_H */