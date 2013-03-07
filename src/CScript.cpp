#include "headers.h"

CScript::CScript()
{/*
    machine=luaL_newstate();
    if(!machine)
    {
        //rzuc bledem
        return;
    }
    luaL_openlibs(machine);*/
}

CScript::~CScript()
{
    //if(machine) lua_close(machine);
}
