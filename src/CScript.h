#ifndef CSCRIPT_H
#define CSCRIPT_H

#include "lua5.2/lua.hpp"

class CScript
{
private:
    lua_State *machine;
protected:
    virtual void RegisterEngineFunctions(){};
public:
    CScript();
    ~CScript();
};

#endif // CSCRIPT_H
