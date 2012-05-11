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

class LuaState
{

public:
    LuaState();
    virtual ~LuaState();
    
    bool loadFile(const String& name);
    ObjectList loadObjects(const String& file, const String& function = "create_scene");
    
    operator lua_State*();
    
private:
    lua_State* L;
};

}

#endif // SPACE_LUASTATE_H
