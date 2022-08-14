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