#include "headers.h"

std::list<CButton*> gButtonClicked;


CButton::~CButton()
{

}

CButton::CButton(guiType typ, sf::Vector2f position, size_t charSize, sf::String text, std::string ActionToDo, std::string ID, bool hide, sf::Color normalColor, sf::Color hoverColor) : CTextBox(position, charSize, text, ID, hide, normalColor)
{
    this->m_actionToDo = ActionToDo;
	this->m_hoverColor = hoverColor;
	this->type = typ;
	
    this->m_clicked = false;
}

void CButton::draw(sf::RenderTarget & target)
{
    if(!(m_text.getPosition()==m_position)) m_text.setPosition(m_position);
	target.draw( m_text );
}

void CButton::update(sf::RenderWindow & App)
{
	if( m_fRect.contains(static_cast<sf::Vector2f>( sf::Mouse::getPosition(App)) ) )
	{
		this->m_text.setColor( m_hoverColor );

        if( CInputHandler::GetInstance()->isToggled(sf::Mouse::Left) && !m_clicked )
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

const std::string *CButton::getAction()
{
	return &m_actionToDo;
}

void CButton::setHoverColor(const sf::Color color)
{
	m_hoverColor = color;
}

void CButton::setAction(const char *text)
{
    m_actionToDo=text;
}

const bool  CButton::wasClicked()
{
	return m_clicked;
}

void CButton::resetState()
{
	m_clicked = false;
}
