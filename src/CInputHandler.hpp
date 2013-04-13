#ifndef CINPUTHANDLER_H
#define CINPUTHANDLER_H

#include "headers.h"

class CInputHandler: public sf::Mouse, public sf::Keyboard, public TSingleton<CInputHandler>
{
public:
    enum KeyState{
        KEY_UP          = 0x01,
        KEY_DOWN        = 0x02,
        KEY_TOGGLED     = 0x04,
        KEY_RELEASED    = 0x08,
    };

    CInputHandler();

    bool isToggled(Key key);
    bool isToggled(Button button);
    bool isReleased(Key key);
    bool isReleased(Button button);

private:
    KeyState m_keyboardState[sf::Keyboard::KeyCount];
    KeyState m_mouseState[sf::Mouse::ButtonCount];

    void refreshStates();
};

#endif // CINPUTHANDLER_H
