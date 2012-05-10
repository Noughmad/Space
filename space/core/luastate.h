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
