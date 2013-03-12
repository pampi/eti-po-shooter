#include "headers.h"

CScript::CScript()
{
    machine=luaL_newstate();
    if(!machine)
    {
        //rzuc bledem
        return;
    }
    luaL_openlibs(machine);
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
                gLogger << gLogger.LOG_WARNING << "Dear dairy, Today's OP is a faggot!\n";
                break;
        }
    }
    //wywolaj f-cje, jesli sie nie wykona to zanotuj o tym w dzienniku KGB/NKWD/SB
    if(lua_pcall(machine, argc-failsafe, 0, 0)!=0) gLogger << gLogger.LOG_WARNING << "Failed to call:" << function_name;
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
