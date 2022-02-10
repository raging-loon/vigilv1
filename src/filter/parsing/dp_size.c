#include "dpsize.h"
#include "rule.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "line_parser.h"
void d_op_parser(struct rule * r, const char * ksub){
  if(isdigit(ksub)){
    r->d_operator = D_OP_JE;
    r->dsize = atoi(ksub);
  } else if(strncmp(ksub,">",1) == 0){
    r->d_operator = D_OP_JG;
    r->dsize = atoi(ksub + 1);
  } else if(strncmp(ksub,"<",1) == 0){
    r->d_operator = D_OP_JL;
    r->dsize = atoi(ksub + 1);
  } else if(strncmp(ksub,"!", 1) == 0){
    r->d_operator = D_OP_NE;
    r->d_operator = atoi(ksub + 1);
  } else if(strncmp(ksub, "<=", 2) == 0){
    r->d_operator = D_OP_JLE;
    r->dsize = atoi(ksub + 2);
  } else if(strncmp(ksub, ">=", 2) == 0){
    r->d_operator = D_OP_JGE;
    r->dsize = atoi(ksub + 2);
  } else {
    printf("Unsupported operator\n");
    exit(-1);
  }
}
