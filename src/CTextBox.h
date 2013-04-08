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

class CTimedTextBox: public CTextBox
{
public:
    CTimedTextBox(sf::Vector2f position, size_t char_size, sf::String text, std::string ID, sf::Int32 visible_time = 0, sf::Color color = sf::Color::Red);

    virtual void draw(sf::RenderTarget &target);
    //
    void SetTimedVisible(sf::Int32 sec);

protected:
    sf::Int32 m_timeOfVisible;

    sf::Clock m_clock;
};

#endif // CLABEL_H
