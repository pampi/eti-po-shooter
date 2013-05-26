#include "headers.h"

CProgressBar::CProgressBar(sf::Vector2f position, std::string ID, int pheight, int pwidth, float startValue, bool hide, std::string imgPath, sf::Color barColor) : CGuiElement(CGuiElement::GUI_BAR, position, ID, hide, barColor)
{
	m_imgPath = imgPath;
	m_width = pwidth;
	m_height = pheight;
	m_value = startValue / 100 * (m_width-20);


	m_textureP = std::make_shared<sf::Texture>( sf::Texture() );
	m_textureP->loadFromImage( *gResources.getImagePointer(imgPath) );
	m_sprite.setTexture( *m_textureP );
	m_sprite.setPosition(m_position);

	m_rShape.setPosition(m_position.x+10, m_position.y+5);
	m_rShape.setSize(sf::Vector2f((float)m_value, (float)m_height-15));
	m_rShape.setFillColor(m_normalColor);
}

void CProgressBar::draw(sf::RenderTarget & target)
{
	target.draw(m_rShape);
	target.draw(m_sprite);
}

int CProgressBar::getWidth() const
{
	return m_width;
}

int CProgressBar::getHeight() const
{
	return m_height;
}

float CProgressBar::getValue() const
{
	return m_value;
}

void CProgressBar::setValue(float value)
{
	m_value = value / 100 * (m_width-20);
	m_rShape.setSize(sf::Vector2f((float)m_value, (float)m_height-15));
}
