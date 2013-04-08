#include "headers.h"

//wartości bool dla Lua
#define LFALSE 0
#define LTRUE 1

int API4Lua::setGUIText(lua_State *vm)
{
    //upewnic sie trzeba ze funkcja zostala wywolana z 2 parametrami
    if(lua_gettop(vm)==2)
    {
        const char* id=lua_tostring(vm, 1);
        const char* text=lua_tostring(vm, 2);

        CGuiElement *gui=gResources.findGUIElement(id);

        if(gui)
        {
            switch(gui->type)
            {
                case CGuiElement::GUI_BUTTON:
                case CGuiElement::GUI_TEXTBOX:
                case CGuiElement::GUI_TIMED_TEXTBOX:
                    {
                        CTextBox *text_container=static_cast<CTextBox *>(gui);
                        text_container->setText(text);
                    }
                    lua_pushboolean(vm, LTRUE);
                    break;
                default:
                    lua_pushboolean(vm, LFALSE);
                    break;
            }
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

        CGuiElement *gui=gResources.findGUIElement(id);

        if(gui)
        {
            if(gui->type==CGuiElement::GUI_BUTTON)
            {
                CButton *btn=static_cast<CButton *>(gui);
                btn->setAction(action);
                lua_pushboolean(vm, LTRUE);
            }
            else lua_pushboolean(vm, LFALSE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setGUIHide(lua_State *vm)
{
    if(lua_gettop(vm)==2)
    {
        const char* id=lua_tostring(vm, 1);
        int hide=lua_toboolean(vm, 2);

        CGuiElement *gui=gResources.findGUIElement(id);

        if(gui)
        {
            gui->setHide((bool)(hide!=LFALSE));
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setGUIPosition(lua_State *vm)
{
    if(lua_gettop(vm)==3)
    {
        const char* id=lua_tostring(vm, 1);
        lua_Number x=lua_tonumber(vm, 2);
        lua_Number y=lua_tonumber(vm, 3);

        CGuiElement *gui=gResources.findGUIElement(id);

        if(gui)
        {
            sf::Vector2f pos(static_cast<float>(x), static_cast<float>(y));
            gui->setPosition(pos);
            lua_pushboolean(vm, LTRUE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);

    return 1;
}

int API4Lua::setGUIColor(lua_State *vm)
{
    if(lua_gettop(vm)==6)
    {
        const char* id=lua_tostring(vm, 1);
        const char* type=lua_tostring(vm, 2);   //"N" - normal | "H" - hover
        unsigned int r=lua_tounsigned(vm, 3);
        unsigned int g=lua_tounsigned(vm, 4);
        unsigned int b=lua_tounsigned(vm, 5);
        unsigned int a=lua_tounsigned(vm, 6);

        CGuiElement *gui=gResources.findGUIElement(id);

        if(gui)
        {
            sf::Color color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b), static_cast<sf::Uint8>(a));

            switch(gui->type)
            {
                case CGuiElement::GUI_BUTTON:
                    {
                        CButton *btn=static_cast<CButton *>(gui);

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
                    }

                    if((type[0]=='N') || (type[0]=='H'))lua_pushboolean(vm, LTRUE);
                    else lua_pushboolean(vm, LFALSE);
                    break;
                case CGuiElement::GUI_TEXTBOX:
                case CGuiElement::GUI_TIMED_TEXTBOX:
                    gui->setNormalColor(color);
                    lua_pushboolean(vm, LTRUE);
                    break;
                default:
                    lua_pushboolean(vm, LFALSE);
                    break;
            }
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
	return 1;
}

int API4Lua::changeLevel(lua_State *vm)
{
    if(lua_gettop(vm)==1)
    {
        int level_to_load = lua_tointeger(vm, 1);
        gResources.loadLevel(level_to_load);
        lua_pushboolean(vm, LTRUE);
    }
    else lua_pushboolean(vm, LFALSE);
    return 1;
}

int API4Lua::logNormal(lua_State *vm)
{
    if(lua_gettop(vm)==1)
    {
        const char* msg=lua_tostring(vm, 1);
        gLogger << CLogger::LOG_INFO << msg;
    }
    return 0;
}

int API4Lua::logWarning(lua_State *vm)
{
    if(lua_gettop(vm)==1)
    {
        const char* msg=lua_tostring(vm, 1);
        gLogger << CLogger::LOG_WARNING << msg;
    }
    return 0;
}

int API4Lua::logError(lua_State *vm)
{
    if(lua_gettop(vm)==1)
    {
        const char* msg=lua_tostring(vm, 1);
        gLogger << CLogger::LOG_ERROR << msg;
    }
	return 0;
}

int API4Lua::playSound(lua_State *vm)
{
    const char* file;
    int loop=LFALSE;
    bool ret_val=false;
    switch(lua_gettop(vm))
    {
        case 2:
            loop=lua_toboolean(vm, 2);
        case 1:
            file=lua_tostring(vm, 1);
            if(CScreenManager::GetInstance()->GetGame()->play(file, (bool)(loop!=LFALSE))) ret_val = true;
            break;
        default:
            break;
    }

    lua_pushboolean(vm, (ret_val==true)?LTRUE:LFALSE);

    return 1;
}

int API4Lua::stopSound(lua_State *vm)
{
    const char* file;
    int all=LFALSE;
    bool ret_val=false;
    switch(lua_gettop(vm))
    {
        case 2:
            all=lua_toboolean(vm, 2);
        case 1:
            file=lua_tostring(vm, 1);
            if(CScreenManager::GetInstance()->GetGame()->stop(file, (bool)(all!=LFALSE))) ret_val = true;
            break;
        default:
            break;
    }

    lua_pushboolean(vm, (ret_val==true)?LTRUE:LFALSE);

    return 1;
}

int API4Lua::stopAllSound(lua_State *vm)
{
	//warning C4100: 'vm' : unreferenced formal parameter
	vm = NULL;

    CScreenManager::GetInstance()->GetGame()->stopAll();

    return 0;
}

int API4Lua::addButton(lua_State *vm)
{
    const char* id, *action, *text;
    unsigned int font_size;
    sf::Vector2f pos;
    if(lua_gettop(vm)==6)
    {
        id=lua_tostring(vm, 1);
        text=lua_tostring(vm, 2);
        action=lua_tostring(vm, 3);
        font_size=lua_tounsigned(vm, 4);
        pos.x=lua_tonumber(vm, 5);
        pos.y=lua_tonumber(vm, 6);

        gResources.addButton(pos, font_size, text, action, id, false);

        lua_pushboolean(vm, LTRUE);
    }
    else lua_pushboolean(vm, LFALSE);
    return 1;
}

int API4Lua::addTextBox(lua_State *vm)
{
    const char* id, *text;
    unsigned int font_size;
    sf::Vector2f pos;
    if(lua_gettop(vm)==5)
    {
        id=lua_tostring(vm, 1);
        text=lua_tostring(vm, 2);
        font_size=lua_tounsigned(vm, 3);
        pos.x=lua_tonumber(vm, 4);
        pos.y=lua_tonumber(vm, 5);

        gResources.addTextBox(pos, font_size, text, id, false);

        lua_pushboolean(vm, LTRUE);
    }
    else lua_pushboolean(vm, LFALSE);
    return 1;
}

int API4Lua::setTimedVisibility(lua_State *vm)
{
    const char* id;
    int i_miliseconds;

    if(lua_gettop(vm)==2)
    {
        CGuiElement *gui_element;
        id=lua_tostring(vm, 1);
        i_miliseconds=lua_tointeger(vm, 2);

        gui_element = gResources.findGUIElement(id);
        if(gui_element)
        {
            if(gui_element->type==CGuiElement::GUI_TIMED_TEXTBOX)
            {
                CTimedTextBox *ptr = (CTimedTextBox *)gui_element;
                ptr->SetTimedVisible(i_miliseconds);
            }
            else lua_pushboolean(vm, LFALSE);
        }
        else lua_pushboolean(vm, LFALSE);
    }
    else lua_pushboolean(vm, LFALSE);
    return 1;
}

int API4Lua::addTimedTextBox(lua_State *vm)
{
    const char* id, *text;
    unsigned int font_size;
    sf::Vector2f pos;
    if(lua_gettop(vm)==5)
    {
        id=lua_tostring(vm, 1);
        text=lua_tostring(vm, 2);
        font_size=lua_tounsigned(vm, 3);
        pos.x=lua_tonumber(vm, 4);
        pos.y=lua_tonumber(vm, 5);

        gResources.addTimedTextBox(pos, font_size, text, id);

        lua_pushboolean(vm, LTRUE);
    }
    else lua_pushboolean(vm, LFALSE);
    return 1;
}
