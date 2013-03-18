#ifndef CLABEL_H
#define CLABEL_H
#include "headers.h"

class CTextBox: public CGuiElement
{
public:
    CTextBox(sf::Vector2f position, size_t charSize, sf::String text, std::string ID, bool hide = true, sf::Color color = sf::Color::Red);

    virtual void draw(sf::RenderTarget & target);

    sf::FloatRect getRect();

    sf::Text *getText();

    const bool isHidden();

    std::string *getID();

    void setHide(bool trueORfalse);

    void setColor(const sf::Color color);

    void setText(const char* text);
    void setPosition(sf::Vector2f position);

    const sf::Vector2f getPosition();

protected:
    size_t m_charSize;
    sf::String m_Text;

    sf::Text m_text;
    sf::FloatRect m_fRect;
    sf::Vector2f m_position;

    sf::Color m_color;

    bool m_hidden;

    std::string m_id;
};

#endif // CLABEL_H
