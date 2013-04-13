#ifndef CSCRIPT_H
#define CSCRIPT_H

#include "headers.h"

struct SLuaArgument
{
    SLuaArgument(){};
    SLuaArgument(bool val);
    SLuaArgument(int val);
    SLuaArgument(unsigned int val);
    SLuaArgument(float val);
    SLuaArgument(const char* val);
    enum{
        BOOLEAN,
        INTEGER,
        UNSIGNED,
        FLOAT,
        CSTRING,
    } type;
    union{
        bool b;
        int i;
        unsigned int u;
        float f;
        const char* sz;
    } data;
};


class CScript
{
private:
    lua_State *machine;

    void RegisterEngineFunctions();

public:
    CScript();
    ~CScript();

    int loadScript(const char* path_to_script);
    //Argumenty musza byc w ciaglym bloku pamieci!
    void callScriptFunction(const char* function_name, int argc=0, SLuaArgument *args=NULL);
};

#endif // CSCRIPT_H
