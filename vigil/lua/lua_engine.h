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

#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H
#include "l_run_condition.h"
#define MAX_LUA_SCRIPTS             20 // for now
struct l_script{
  char filename[64];
  struct l_run_condition conditions;
};

extern struct l_script lua_scripts[MAX_LUA_SCRIPTS];

void collect_scripts();


void run_hello_script();

#endif /* LUA_ENGINE_H */