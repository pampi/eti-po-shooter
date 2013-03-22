﻿#include "headers.h"

CScript::CScript()
{
    machine=luaL_newstate();
    if(!machine)
    {
        //rzuc bledem
        return;
    }
    //inicjacja przydatnych bibliotek standardowych Lua
    luaL_openlibs(machine);

    //powiaz funkcje silnika z interfejsem Lua
    RegisterEngineFunctions();

	pGlobal.gLogger << pGlobal.gLogger.LOG_INFO << "CScript konstruktor";
}

CScript::~CScript()
{
    if(machine) lua_close(machine);
}

int CScript::loadScript(const char *path_to_script)
{
    return luaL_dofile(machine, path_to_script);
}

void CScript::callScriptFunction(const char *function_name, int argc, SLuaArgument *args)
{
    int failsafe=0;
    //znajdz funkcje
    lua_getglobal(machine, function_name);
    //wrzuc argumenty funkcji na STOS
    for(int i=0; i<argc; i++)
    {
        switch(args[i].type)
        {
            case SLuaArgument::BOOLEAN:
                lua_pushboolean(machine, static_cast<int>(args[i].data.b));
                break;
            case SLuaArgument::CSTRING:
                lua_pushstring(machine, args[i].data.sz);
                break;
            case SLuaArgument::FLOAT:
                lua_pushnumber(machine, static_cast<lua_Number>(args[i].data.f));
                break;
            case SLuaArgument::INTEGER:
                lua_pushinteger(machine, static_cast<lua_Integer>(args[i].data.i));
                break;
            case SLuaArgument::UNSIGNED:
                lua_pushunsigned(machine, args[i].data.u);
                break;
            default:
                failsafe++;
                pGlobal.gLogger << pGlobal.gLogger.LOG_WARNING << "Dear dairy, Today's OP is a faggot!\n";
                break;
        }
    }
    //wywolaj f-cje, jesli sie nie wykona to zanotuj o tym w dzienniku KGB/NKWD/SB
    if(lua_pcall(machine, argc-failsafe, 0, 0)!=0) 
		pGlobal.gLogger << pGlobal.gLogger.LOG_WARNING << std::string("Failed to call:" )+function_name;
}

void CScript::RegisterEngineFunctions()
{
    //GUI

    //setButtonText(id, text)
    lua_register(machine, "setButtonText", API4Lua::setButtonText);
    //setButtonAction(id, action)
    lua_register(machine, "setButtonAction", API4Lua::setButtonAction);
    //setButtonHide(id, boolean true/false)
    lua_register(machine, "setButtonHide", API4Lua::setButtonHide);
    //setButtonPosition(id, double x, double y)
    lua_register(machine, "setButtonPosition", API4Lua::setButtonPosition);
    //setButtonColor(id, "N"/"H", r, g, b, a)
    lua_register(machine, "setButtonColor", API4Lua::setButtonColor);

    //audio
    //playSound(file, [loop])
    lua_register(machine, "playSound", API4Lua::playSound);
    //stopSound(file, [all]);
    lua_register(machine, "stopSound", API4Lua::stopSound);
    //stopAllSound()
    lua_register(machine, "stopSoundAll", API4Lua::stopAllSound);


    //mix
    //addScript(path_to_script)
    lua_register(machine, "addScript", API4Lua::loadAdditionalScript);
    //changeLevel(lvl_id)
    lua_register(machine, "changeLevel", API4Lua::changeLevel);
    //logNormal(message)
    lua_register(machine, "logNormal", API4Lua::logNormal);
    //logWarning(message)
    lua_register(machine, "logWarning", API4Lua::logWarning);
    //logError(message)
    lua_register(machine, "logError", API4Lua::logError);
}

SLuaArgument::SLuaArgument(bool val)
{
    type=BOOLEAN;
    data.b=val;
}

SLuaArgument::SLuaArgument(const char *val)
{
    type=CSTRING;
    data.sz=val;
}

SLuaArgument::SLuaArgument(float val)
{
    type=FLOAT;
    data.f=val;
}

SLuaArgument::SLuaArgument(int val)
{
    type=INTEGER;
    data.i=val;
}

SLuaArgument::SLuaArgument(unsigned int val)
{
    type=UNSIGNED;
    data.u=val;
}
