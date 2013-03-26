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

    void setText(const char* text);

protected:
    size_t m_charSize;

    sf::Text m_text;
};

#endif // CLABEL_H
