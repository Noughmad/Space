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

#ifndef SPACE_LUASTATE_H
#define SPACE_LUASTATE_H

#include "types.h"

class lua_State;

namespace Space {

class IObject;

/**
 * @brief Loads and executes Lua scripts
 * 
 * This class provides convenience functions for working with the Lua scripting environment. 
 * 
 **/
class LuaState
{

public:
    LuaState();
    virtual ~LuaState();
    
    /**
     * Loads a file and executes its contents. 
     *
     * @param name the file to load
     * @return true if the loading was successful, false otherwise
     **/
    bool loadFile(const String& name);
    /**
     * @brief Loads objects from a Lua file
     * 
     * This functions loads the file @p file and runs the function @p function. 
     * If the specified function returns one or more IObject instances, 
     * they are return. 
     *
     * @param file the file to load
     * @param function the function in the file to run, defaults to "create_scene".
     * @return the newly loaded objects
     **/
    ObjectList loadObjects(const String& file, const String& function = "create_scene");
    
    /**
     * Allows a LuaState to be implicitely used as an argument to functions in the Lua C API
     *
     **/
    operator lua_State*();
    
private:
    lua_State* L;
};

}

#endif // SPACE_LUASTATE_H
