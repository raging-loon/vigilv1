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
#include "lua_engine.h"
//TODO: vvvvv make this work with more versions of lua
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "utils.h"
lua_State * l;
char * l_script;

void l_init(){
  l = luaL_newstate();
  luaL_openlibs(l);
}
void set_script_file_size(int flen){
  l_script = (char *)malloc(sizeof(char) * flen);
}
void l_destroy(){
  if(l_script)
    free(l_script);

  lua_close(l);
}

void l_rule_alert(const struct rule_data * rdata, const struct rule * r, int x){

  lua_pushstring(l,rdata->src_ip_addr);
  lua_setglobal(l,"src_ip_addr");

  lua_pushstring(l,rdata->dest_ip_addr);
  lua_setglobal(l,"dest_ip_addr");
  
  lua_pushstring(l,r->message);
  lua_setglobal( l,"message");
  
  lua_pushinteger(l,(int)rdata->dest_port);
  lua_setglobal(l,"dest_port");

  lua_pushinteger(l,(int)rdata->src_port);
  lua_setglobal(l,"src_port");

  lua_pushstring(l,get_formated_time());
  lua_setglobal(l,"time");

  lua_pushinteger(l,rdata->__protocol);
  lua_setglobal(l,"protocol");

  if(luaL_dofile(l,l_script) == LUA_OK){
    lua_pop(l,lua_gettop(l));
  }
  // clear the stack so old alerts don't cause problems
  lua_settop(l, 0);
}
