#include "headers.h"

CTextBox::CTextBox(sf::Vector2f position, size_t charSize, sf::String text, std::string ID, bool hide, sf::Color color) : CGuiElement(position, ID, hide, color)
{
    type = GUI_TEXTBOX;
    m_position = position;
    m_charSize = charSize;

    m_text.setFont( gResources.getFont() );
    m_text.setString( text );
    m_text.setCharacterSize( charSize );
    m_text.setColor( color );
    m_text.setPosition( position );

    m_fRect=m_text.getGlobalBounds();
}

void CTextBox::draw(sf::RenderTarget & target)
{
    if(!(m_text.getPosition()==m_position)) m_text.setPosition(m_position);
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

void CTextBox::setText(const char *text)
{
    m_text.setString( text );
    m_fRect=m_text.getGlobalBounds();
}

CTimedTextBox::CTimedTextBox(sf::Vector2f position, size_t char_size, sf::String text, std::string ID, sf::Int32 visible_time, sf::Color color) : CTextBox(position, char_size, text, ID, true, color)
{
    type = GUI_TIMED_TEXTBOX;

    if(visible_time>0)
    {
        m_clock.restart();
        m_timeOfVisible = visible_time;
    }
}

void CTimedTextBox::SetTimedVisible(sf::Int32 sec)
{
    if(sec>0)
    {
        m_timeOfVisible = sec;
        m_clock.restart();
    }
}

void CTimedTextBox::draw(sf::RenderTarget & target)
{
    if(m_clock.getElapsedTime().asMilliseconds() < m_timeOfVisible)
    {
        if(!(m_text.getPosition()==m_position)) m_text.setPosition(m_position);
        target.draw( m_text );
    }
}
