#ifndef API4LUA_H
#define API4LUA_H
#include "headers.h"

namespace API4Lua
{
//GUI API
    //id, text, action, font_size, x, y
    int addButton(lua_State *vm);
    //id, text, font_size, x, y
    int addTextBox(lua_State *vm);
    //id, text, font_size, x, y
    int addTimedTextBox(lua_State *vm);

    //id, action
    int setButtonAction(lua_State *vm);

    //id, miliseconds
    int setTimedVisibility(lua_State *vm);

    //id, text
    int setGUIText(lua_State *vm);
    //id, want to hide?
    int setGUIHide(lua_State *vm);
    //id, position
    int setGUIPosition(lua_State *vm);
    //id, "N"/"H", r, g, b, a | NormalColor
    int setGUIColor(lua_State *vm);

//ADUIO API
    //file, loop
    int playSound(lua_State *vm);
    //file, all
    int stopSound(lua_State *vm);
    //nic
    int stopAllSound(lua_State *vm);

//Player
    //void
    int getPlayerPosition(lua_State *vm);
    //x, y
    int setPlayerPosition(lua_State *vm);
    //anim
    int changePlayerState(lua_State *vm);

//MIX API
    //path to script
    int loadAdditionalScript(lua_State *vm);
    //level_id
    int changeLevel(lua_State *vm);
	//game_state
	int changeGameState(lua_State *vm);
    //log_message
    int logNormal(lua_State *vm);
    //log_message
    int logWarning(lua_State *vm);
    //log_message
    int logError(lua_State *vm);
}

#endif
