/*     
    This file is part of Vigil.

    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, either version 3 
    of the License, or (at your option) any later version.

    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with Vigil. 
    If not, see <https://www.gnu.org/licenses/>. 

*/


#include "dp_size.h"
#include "../../config/rule.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../config/line_parser.h"
void d_op_parser(struct rule * r, const char * ksub,int type){
  


  if(str_isdigit(ksub)){  
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
   r->dsize = atoi(ksub + 1);
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


bool d_engine(const struct rule* r, const struct rule_data * rdata){

  if(r->d_operator == -1) {
    return true;
  }
  switch(r->d_operator){
    case D_OP_JE:

      if(r->dsize == rdata->dsize) return true;
      break;
    case D_OP_JG:
      if(rdata->dsize > r->dsize) return true;
      break;
    case D_OP_JGE:
      if(rdata->dsize >= r->dsize) return true;
      break;
    case D_OP_JL:
      if(rdata->dsize < r->dsize) return true;
      break;
    case D_OP_JLE:
      if(rdata->dsize <= r->dsize) return true;
      break;
    case D_OP_NE:
      if(rdata->dsize != r->dsize) return true;
      break;
  }
  return false;
}
