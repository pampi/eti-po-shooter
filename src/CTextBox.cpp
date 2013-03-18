#include "headers.h"

CTextBox::CTextBox(sf::Vector2f position, size_t charSize, sf::String text, std::string ID, bool hide, sf::Color color)
{
    type = GUI_TEXTBOX;
    m_position = position;
    m_charSize = charSize;
    m_Text=text;
    m_id=ID;
    m_hidden=hide;
    m_color=color;
}

void CTextBox::draw(sf::RenderTarget & target)
{
    target.draw( m_text );
}

sf::FloatRect CTextBox::getRect()
{
    return m_text.getGlobalBounds();
}

sf::Text *CTextBox::getText()
{
    return &m_text;
}

const bool CTextBox::isHidden()
{
    return m_hidden;
}

void CTextBox::setHide(bool trueORfalse)
{
    m_hidden = trueORfalse;
}

void CTextBox::setColor(const sf::Color color)
{
    m_color = color;
}

const sf::Vector2f CTextBox::getPosition()
{
    return m_position;
}

std::string *CTextBox::getID()
{
    return &m_id;
}

void CTextBox::setPosition(sf::Vector2f position)
{
    m_position=position;
}

void CTextBox::setText(const char *text)
{
    m_text.setString( sf::String(text) );
    m_fRect=m_text.getGlobalBounds();
}
