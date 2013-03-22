#include "headers.h"

CInputHandler *CInputHandler::m_pInstance = 0;

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

	pGlobal.gLogger << pGlobal.gLogger.LOG_INFO << "CInputHandler konstruktor";
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

CInputHandler *CInputHandler::GetInstance()
{
    if(!CInputHandler::m_pInstance) CInputHandler::m_pInstance = new CInputHandler();
    return CInputHandler::m_pInstance;
}
