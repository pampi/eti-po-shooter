#include "headers.h"

CButton::CButton()
{

}

CButton::CButton(guiType typ, sf::Vector2f position, size_t charSize, sf::String text, std::string ActionToDo, std::string ID, bool hide, sf::Color normalColor, sf::Color hoverColor)
{
	this->m_position = position;
	this->m_charSize = charSize;
	this->m_buttonText = text;
	this->m_actionToDo = ActionToDo;
	this->m_normalColor = normalColor;
	this->m_hoverColor = hoverColor;
	this->m_hidden = hide;
	this->m_id = ID;
	this->type = typ;
	
	this->m_clicked = false;

	m_text.setPosition( position );
	m_text.setFont( gResources.getFont() );
	m_text.setString( m_buttonText );
	m_text.setCharacterSize( charSize );
	m_text.setColor( normalColor );

	m_fRect = m_text.getGlobalBounds();
}

void CButton::draw(sf::RenderTarget & target)
{
	target.draw( m_text );
}

void CButton::update(sf::RenderWindow & App)
{
	if( m_fRect.contains(static_cast<sf::Vector2f>( sf::Mouse::getPosition(App)) ) )
	{
		this->m_text.setColor( m_hoverColor );

		if( sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_clicked )
		{
			gButtonClicked.push_back( this );
			m_clicked = true;
            //DEBUG TO DEL
			//std::cout<<this->m_actionToDo<<std::endl;
		}
	}
	else
	{
		this->m_text.setColor( m_normalColor );
	}
}

sf::FloatRect CButton::getRect()
{
	return m_text.getGlobalBounds();
}

sf::Text *CButton::getText()
{
	return &m_text;
}

const bool CButton::isHidden()
{
	return m_hidden;
}

const std::string *CButton::getAction()
{
	return &m_actionToDo;
}

void CButton::setHide(bool trueORfalse)
{
	m_hidden = trueORfalse;
}

void CButton::setNormalColor(const sf::Color color)
{
	m_normalColor = color;
}

void CButton::setHoverColor(const sf::Color color)
{
	m_hoverColor = color;
}

const sf::Vector2f CButton::getPosition()
{
	return m_position;
}

std::string *CButton::getID()
{
	return &m_id;
}

void CButton::setAction(const char *text)
{
    m_actionToDo=text;
}

void CButton::setPosition(sf::Vector2f position)
{
    m_position=position;
}

void CButton::setText(const char *text)
{
    m_text.setString( sf::String(text) );
    m_fRect=m_text.getGlobalBounds();
}

const bool  CButton::wasClicked()
{
	return m_clicked;
}

void CButton::resetState()
{
	m_clicked = false;
}
