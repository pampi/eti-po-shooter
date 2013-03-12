#ifndef API4LUA_H
#define API4LUA_H
#include "headers.h"

namespace API4Lua
{
//GUI API
    //id, text
    int setButtonText(lua_State *vm);
    //id, action
    int setButtonAction(lua_State *vm);
    //id, want to hide?
    int setButtonHide(lua_State *vm);
    //id, position
    int setButtonPosition(lua_State *vm);
    //id, "N"/"H", r, g, b, a | NormalColor
    int setButtonColor(lua_State *vm);

//ADUIO API


//MIX API
    int loadAdditionalScript(lua_State *vm);
}

#endif
