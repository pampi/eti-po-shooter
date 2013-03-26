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
