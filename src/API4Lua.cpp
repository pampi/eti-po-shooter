#include "API4Lua.h"

//wartości bool dla Lua
#define LFALSE 0
#define LTRUE 1

int API4Lua::setButtonText(lua_State *vm)
{
    //upewnic sie trzeba ze funkcja zostala wywolana z 2 parametrami
    if(lua_gettop(vm)==2)
    {
        const char* id=lua_tostring(vm, 1);
        const char* text=lua_tostring(vm, 2);

        CButton *btn=gResources.findButton(id);

        if(btn)
        {
            btn->setText(text);
            lua_pushboolean(vm, LTRUE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setButtonAction(lua_State *vm)
{
    if(lua_gettop(vm)==2)
    {
        const char* id=lua_tostring(vm, 1);
        const char* action=lua_tostring(vm, 2);

        CButton *btn=gResources.findButton(id);

        if(btn)
        {
            btn->setAction(action);
            lua_pushboolean(vm, LTRUE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setButtonHide(lua_State *vm)
{
    if(lua_gettop(vm)==2)
    {
        const char* id=lua_tostring(vm, 1);
        int hide=lua_toboolean(vm, 2);

        CButton *btn=gResources.findButton(id);

        if(btn)
        {
            btn->setHide((bool)(hide!=LFALSE));
            lua_pushboolean(vm, LTRUE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setButtonPosition(lua_State *vm)
{
    if(lua_gettop(vm)==3)
    {
        const char* id=lua_tostring(vm, 1);
        lua_Number x=lua_tonumber(vm, 2);
        lua_Number y=lua_tonumber(vm, 3);

        CButton *btn=gResources.findButton(id);

        if(btn)
        {
            sf::Vector2f pos(static_cast<float>(x), static_cast<float>(y));
            btn->setPosition(pos);
            lua_pushboolean(vm, LTRUE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setButtonColor(lua_State *vm)
{
    if(lua_gettop(vm)==6)
    {
        const char* id=lua_tostring(vm, 1);
        const char* type=lua_tostring(vm, 2);   //"N" - normal | "H" - hover
        unsigned int r=lua_tounsigned(vm, 3);
        unsigned int g=lua_tounsigned(vm, 4);
        unsigned int b=lua_tounsigned(vm, 5);
        unsigned int a=lua_tounsigned(vm, 6);

        CButton *btn=gResources.findButton(id);

        if(btn)
        {
            sf::Color color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b), static_cast<sf::Uint8>(a));

            switch(type[0])
            {
                case 'N':
                    btn->setNormalColor(color);
                    break;
                case 'H':
                    btn->setHoverColor(color);
                    break;
                default: break;
            }

            if((type[0]=='N') || (type[0]=='H'))lua_pushboolean(vm, LTRUE);
            else lua_pushboolean(vm, LFALSE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::loadAdditionalScript(lua_State *vm)
{
    if(lua_gettop(vm)==1)
    {
        const char* script_path=lua_tostring(vm, 1);
        if(CScreenManager::GetInstance()->GetGame()->loadScript(script_path)==0)
        {
            lua_pushboolean(vm, LTRUE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);
}
