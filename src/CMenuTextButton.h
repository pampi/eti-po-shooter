#ifndef CMENUTXTBUT_H
#define CMENUTXTBUT_H

#include "headers.h"

class CMenuTextButton : public CTextButton
{
public:
	// chce �eby tworz�c ten obiekt, wykona� si� tak samo jak konstruktor CTextButton, ale nie wiem jak to zrobi�
	// @EDIT: za wuja nie wiem czemu tak jak jest teraz dziala ;d
	CMenuTextButton(sf::Vector2f position, size_t size, sf::String text, int returnsAction, sf::Color def, sf::Color hover) : CTextButton(position, size, text, returnsAction)
	{
		this->m_default = def;
		this->m_hover = hover;
	}

	virtual void draw(sf::RenderWindow & App);
	virtual void eventUpdate(sf::Event & event);
	virtual void update(sf::RenderWindow & App);

	void setFont(const sf::Font & font);
	

private:
	sf::Color m_default, m_hover;
	
};
#endif