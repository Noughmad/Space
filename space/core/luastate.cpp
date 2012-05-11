/*
 * Copyright 2012 Miha Čančula <miha@noughmad.eu>
 * This file is a part of Space, a library for space simulations
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

