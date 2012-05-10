#ifndef SPACE_LUASTATE_H
#define SPACE_LUASTATE_H

#include "types.h"

class lua_State;

namespace Space {

class LuaState
{

public:
    LuaState();
    virtual ~LuaState();
    
    bool loadFile(const String& name);
    
    operator lua_State*();
    
private:
    lua_State* L;
};

}

#endif // SPACE_LUASTATE_H
