#ifndef CTXTBUT_H
#define CTXTBUT_H

#include "headers.h"

class CTextButton
{
public:
	virtual void draw(sf::RenderWindow & App)=0;
	virtual void eventUpdate(sf::Event & event)=0;
	virtual void update(sf::RenderWindow & App)=0;

	CTextButton(sf::Vector2f position, size_t size, sf::String text, int returnsAction)
	{
		this->m_size = size;
		this->m_string = text;
		this->m_returnAction = returnsAction;
		this->m_position = position;

		m_text.setCharacterSize(m_size);
		m_text.setString(text);
		m_text.setPosition(m_position);


		m_fRect = m_text.getGlobalBounds();		
	}

	sf::FloatRect& getRect()
	{
		return m_fRect;
	}


protected:
	size_t m_size;
	sf::String m_string;
	int m_returnAction;
	sf::Text m_text;
	sf::FloatRect m_fRect;
	sf::Vector2f m_position;
};
#endif