#include "headers.h"

const char *szUndefined="NOT DEFINED";
const char *strKey[sf::Keyboard::KeyCount];

CInputHandler::CInputHandler()
{
    for(int i=0; i<sf::Keyboard::KeyCount; i++)
    {
        if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
        {
            m_keyboardState[i]=static_cast<KeyState>(KEY_DOWN|KEY_TOGGLED);
        }
        else m_keyboardState[i]=KEY_UP;
    }
    for(int i=0; i<sf::Mouse::ButtonCount; i++)
    {
        if(sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i)))
        {
            m_mouseState[i]=static_cast<KeyState>(KEY_DOWN|KEY_TOGGLED);
        }
        else m_mouseState[i]=KEY_UP;
    }

    for(int i=0; i<sf::Keyboard::KeyCount; i++)
    {
        strKey[i]=szUndefined;
    }

    strKey[sf::Keyboard::A]="A";
    strKey[sf::Keyboard::B]="B";
    strKey[sf::Keyboard::C]="C";
    strKey[sf::Keyboard::D]="D";
    strKey[sf::Keyboard::E]="E";
    strKey[sf::Keyboard::F]="F";
    strKey[sf::Keyboard::G]="G";
    strKey[sf::Keyboard::H]="H";
    strKey[sf::Keyboard::I]="I";
    strKey[sf::Keyboard::J]="J";
    strKey[sf::Keyboard::K]="K";
    strKey[sf::Keyboard::L]="L";
    strKey[sf::Keyboard::M]="M";
    strKey[sf::Keyboard::N]="N";
    strKey[sf::Keyboard::O]="O";
    strKey[sf::Keyboard::P]="P";
    strKey[sf::Keyboard::Q]="Q";
    strKey[sf::Keyboard::R]="R";
    strKey[sf::Keyboard::S]="S";
    strKey[sf::Keyboard::T]="T";
    strKey[sf::Keyboard::U]="U";
    strKey[sf::Keyboard::V]="V";
    strKey[sf::Keyboard::W]="W";
    strKey[sf::Keyboard::X]="X";
    strKey[sf::Keyboard::Y]="Y";
    strKey[sf::Keyboard::Z]="Z";

    strKey[sf::Keyboard::Up]="UP";
    strKey[sf::Keyboard::Down]="DOWN";
    strKey[sf::Keyboard::Left]="LEFT";
    strKey[sf::Keyboard::Right]="RIGHT";

    strKey[sf::Keyboard::Space]="SPACEBAR";
    strKey[sf::Keyboard::Escape]="ESC";
    strKey[sf::Keyboard::Return]="RETURN";
    strKey[sf::Keyboard::Tab]="TAB";

    gLogger << CLogger::LOG_INFO << "CInputHandler konstruktor";
}

void CInputHandler::refreshStates()
{
    //keyboard states
    for(int i=0; i<KeyCount; i++)
    {
        if((m_keyboardState[i]&KEY_UP) && (isKeyPressed(static_cast<Key>(i))))
        {
            m_keyboardState[i]=static_cast<KeyState>(KEY_DOWN|KEY_TOGGLED);
        }
        else
        {
            if((m_keyboardState[i]&KEY_DOWN) && (!isKeyPressed(static_cast<Key>(i))))
            {
                m_keyboardState[i]=static_cast<KeyState>(KEY_UP|KEY_RELEASED);
            }
        }
    }

    //mouse states
    for(int i=0; i<ButtonCount; i++)
    {
        if((m_mouseState[i]&KEY_UP) && (isButtonPressed(static_cast<Button>(i))))
        {
            m_mouseState[i]=static_cast<KeyState>(KEY_DOWN|KEY_TOGGLED);
        }
        else
        {
            if((m_mouseState[i]&KEY_DOWN) && (!isButtonPressed(static_cast<Button>(i))))
            {
                m_mouseState[i]=static_cast<KeyState>(KEY_UP|KEY_RELEASED);
            }
        }
    }
}

bool CInputHandler::isToggled(Button button)
{
    bool ret_val=false;
    refreshStates();
    if(m_mouseState[button]&KEY_TOGGLED)
    {
        ret_val=true;
        m_mouseState[button]=KEY_DOWN;
    }
    return ret_val;
}

bool CInputHandler::isToggled(Key key)
{
    bool ret_val=false;
    refreshStates();
    if(m_keyboardState[key]&KEY_TOGGLED)
    {
        ret_val=true;
        m_keyboardState[key]=KEY_DOWN;
    }
    return ret_val;
}

bool CInputHandler::isReleased(Button button)
{
    bool ret_val=false;
    refreshStates();
    if(m_mouseState[button]&KEY_RELEASED)
    {
        ret_val=true;
        m_mouseState[button]=KEY_UP;
    }
    return ret_val;
}

bool CInputHandler::isReleased(Key key)
{
    bool ret_val=false;
    refreshStates();
    if(m_keyboardState[key]&KEY_RELEASED)
    {
        ret_val=true;
        m_keyboardState[key]=KEY_UP;
    }
    return ret_val;
}
