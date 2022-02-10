#include "dp_size.h"
#include "rule.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "line_parser.h"
void d_op_parser(struct rule * r, const char * ksub,int type){
  int * op;
  int * size;
  if(type == 1){
    op = &r->d_operator;
    size = &r->dsize;
  } else {
    op = &r->p_operator;
    size = &r->psize;
  }
  //  = &r->d_operator
  


  if(isdigit(ksub)){  
   *op = D_OP_JE;
   *size = atoi(ksub);

  } else if(strncmp(ksub,">",1) == 0){
   *op = D_OP_JG;
   *size = atoi(ksub + 1);
  } else if(strncmp(ksub,"<",1) == 0){
   *op = D_OP_JL;
   *size = atoi(ksub + 1);
  } else if(strncmp(ksub,"!", 1) == 0){
   *op = D_OP_NE;
   *size = atoi(ksub + 1);
  } else if(strncmp(ksub, "<=", 2) == 0){
   *op = D_OP_JLE;
   *size = atoi(ksub + 2);
  } else if(strncmp(ksub, ">=", 2) == 0){
   *op = D_OP_JGE;
   *size = atoi(ksub + 2);
  } else {
    printf("Unsupported operator\n");
    exit(-1);
  }
}


bool d_engine(const struct rule* r, const struct rule_data * rdata){
  if(r->d_operator == -1) return false;
  printf("e");
  switch(r->d_operator){
    case D_OP_JE:
      if(r->dsize == rdata->pkt_len) return true;
      break;
    case D_OP_JG:
      if(rdata->pkt_len > r->dsize) return true;
      break;
    case D_OP_JGE:
      if(rdata->pkt_len >= r->dsize) return true;
      break;
    case D_OP_JL:
      if(rdata->pkt_len < r->dsize) return true;
      break;
    case D_OP_JLE:
      if(rdata->pkt_len <= r->dsize) return true;
      break;
    case D_OP_NE:
      if(rdata->pkt_len != r->dsize) return true;
      break;
  }
  return false;
}
