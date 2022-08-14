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


#ifndef DPSIZE_H
#define DPSIZE_H
#include "engine/rule/rule.h"


#define D_OP_JE                 0xa1
#define D_OP_JL                 0xa2
#define D_OP_JLE                0xa3
#define D_OP_JG                 0xa4
#define D_OP_JGE                0xa5
#define D_OP_NE                 0xa6

void d_op_parser(struct rule *, const char *, int );

bool d_engine(const struct rule*, const struct rule_data *);


#endif /*DPSIZE_H */