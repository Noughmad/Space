#include "luastate.h"

#include "tolua++.h"
#include "lua_space_core.h"

extern "C" {
#include "lualib.h"
}

using namespace Space;

LuaState::LuaState() : L()
{
    L = lua_open();
    tolua_space_core_open(L);
    
    // Load the basic libraries that should be available to scripts
    lua_pushcfunction(L,luaopen_base);
    lua_call(L,0,0);
    lua_pushcfunction(L,luaopen_math);
    lua_call(L,0,0);
    lua_pushcfunction(L,luaopen_string);
    lua_call(L,0,0);
    lua_pushcfunction(L,luaopen_table);
    lua_call(L,0,0);
}

LuaState::~LuaState()
{
    lua_close(L);
}

LuaState::operator lua_State*()
{
    return L;
}

bool LuaState::loadFile(const String& name)
{
    luaL_dofile(L, name.c_str());
    lua_getglobal(L, "test");
    lua_pushstring(L, "Space Test");
    lua_call(L, 1, 0);
    return true;
}
