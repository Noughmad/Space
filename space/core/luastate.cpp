#include "luastate.h"
#include "iobject.h"

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
    return true;
}

ObjectList LuaState::loadObjects(const String& file, const String& function)
{
    loadFile(file);
    int level = lua_gettop(L);

    // Push the function onto the stack
    lua_getglobal(L, function.c_str());
    
    ObjectList set;

    // Execute the function
    if (lua_pcall(L, 0, LUA_MULTRET, 0) != 0)
    {
        // Something went wrong with the function call
        return set;
    }
    
    int m = lua_gettop(L);
    int n = lua_gettop(L) - level;
    for (int i = level+1; i <= m; ++i)
    {
        if (lua_isuserdata(L, i))
        {
            IObject* object = *(IObject**)lua_touserdata(L, i);
            if (object)
            {
                set.push_back(object);
            }
        }
    }
    
    lua_pop(L, n);
    
    std::cout << "Loaded " << set.size() << " objects from " << file << std::endl;
    return set;
}

