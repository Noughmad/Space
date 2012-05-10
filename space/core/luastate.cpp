#include "luastate.h"

#include "tolua++.h"
#include "lua_space_core.h"

using namespace Space;

LuaState::LuaState() : mState()
{
    mState = lua_open();
    tolua_space_core_open(mState);
}

LuaState::~LuaState()
{
    lua_close(mState);
}

LuaState::operator lua_State*()
{
    return mState;
}

bool LuaState::loadFile(const String& name)
{
    return !luaL_loadfile(mState, name.c_str()) && !lua_pcall(mState, 0, LUA_MULTRET, 0);
}
