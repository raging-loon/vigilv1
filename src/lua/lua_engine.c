#include "lua_engine.h"
//TODO: vvvvv make this work with more versions of lua
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>

void run_hello_script(){
  lua_State * l = luaL_newstate();

  luaL_openlibs(l);

  if(luaL_dofile(l,"src/lua/scripts/hellotest.lua") == LUA_OK){
    lua_pop(l,lua_gettop(l));
  }
  lua_close(l);
}