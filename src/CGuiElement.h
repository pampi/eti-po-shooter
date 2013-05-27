#ifndef CGUIELE_H
#define CGUIELE_H

#include "headers.h"

class CGuiElement
{
public:
	enum guiType { GUI_NOPE, GUI_BUTTON, GUI_BAR, GUI_TEXTBOX, GUI_TIMED_TEXTBOX, GUI_STATIC_OVERLAY, GUI_HIDDEN_BUTTON };
	guiType type;

	virtual void draw(sf::RenderTarget & target)=0;

    CGuiElement(guiType pType ,sf::Vector2f position, std::string ID, bool hide = true, sf::Color normalColor = sf::Color::Red)
    {
        m_position = position;
        m_id = ID;
        m_hidden = hide;
        m_normalColor = normalColor;
		type = pType;
    }

    virtual ~CGuiElement(){}

    const bool isHidden()
    {
        return m_hidden;
    }

    std::string *getID()
    {
        return &m_id;
    }

    const sf::Vector2f getPosition()
    {
        return m_position;
    }

    void setHide(bool trueORfalse)
    {
        m_hidden = trueORfalse;
    }

    void setNormalColor(const sf::Color color)
    {
        m_normalColor = color;
    }

    void setPosition(sf::Vector2f position)
    {
        m_position = position;
    }

protected:
    sf::FloatRect m_fRect;
    sf::Vector2f m_position;

    sf::Color m_normalColor;

    bool m_hidden;

    std::string m_id;
};
#endif
