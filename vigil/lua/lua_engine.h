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

#include "../filter/parsing/rule.h"
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>
extern char * l_script;
extern lua_State * l;

void l_init();
void l_destroy();
void set_script_file_size(int);
void l_rule_alert(const struct rule_data *, const struct rule *, int);
#endif /* LUA_ENGINE_H */