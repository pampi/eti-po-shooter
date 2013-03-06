#include "headers.h"



void CMenuTextButton::draw(sf::RenderWindow & App)
{
	App.draw(this->m_text);
}

void CMenuTextButton::eventUpdate(sf::Event & event)
{

}

void CMenuTextButton::update(sf::RenderWindow & App)
{
	if( this->getRect().contains( (float)sf::Mouse::getPosition(App).x, (float)sf::Mouse::getPosition(App).y) )
	{
		m_text.setColor( m_hover );
	}
	else
	{
		m_text.setColor( m_default );
	}
}

void CMenuTextButton::setFont(const sf::Font & font)
{
	this->m_text.setFont( font );
	this->getRect() = m_text.getGlobalBounds();
}