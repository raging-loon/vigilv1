#include "lua_engine.h"
//TODO: vvvvv make this work with more versions of lua
#include <lua5.3/lua.h>
#include <lua5.3/lauxlib.h>
#include <lua5.3/lualib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
struct l_script lua_scripts[MAX_LUA_SCRIPTS];


void run_hello_script(){
  lua_State * l = luaL_newstate();
  
  luaL_openlibs(l);
  // lua_setglobal(l,"y");

  if(luaL_dofile(l,"src/lua/scripts/hellotest.lua") == LUA_OK){
    lua_pop(l,lua_gettop(l));
  }
  lua_close(l);
}

void collect_scripts(){
  FILE * fp = fopen("/etc/vigil/lscript.conf","r");
  
  if(fp == NULL){
    printf("Failed to collect Lua scripts: /etc/vigil/lscript.conf not found.\n");
    exit(-1); // the engineer should fix this
  }  
  
  size_t pos, len;
  char * line = NULL;
  char lscript_root[40];

  regex_t lua_rgx;
  if(regcomp(&lua_rgx,".*\.lua:.*",0);


  while((pos = getline(&line,&len,fp)) != -1){
    if(line[0] == '#') continue;
    if(strncmp(line,"l_script_root=",14) == 0){
      strcpy(lscript_root,line+14);
      lscript_root[strcspn(lscript_root,"\n")] = 0;
    } 
    else if(regexec(&lua_rgx,line,0,NULL,0) == 0){
      // printf("Lua script found: %s",line);
      
    }
  } 
}