#include "headers.h"

CGuiOverlay::CGuiOverlay(sf::Vector2f position, std::string ID, int pheight, int pwidth, bool hide, std::string imgPath) : CGuiElement(CGuiElement::GUI_STATIC_OVERLAY ,position, ID, hide)
{
	m_imgPath = imgPath;
	m_width = pwidth;
	m_height = pheight;

	m_textureP = std::make_shared<sf::Texture>( sf::Texture() );
	m_textureP->loadFromImage( *gResources.getImagePointer(imgPath) );
	m_sprite.setTexture( *m_textureP );
	m_sprite.setPosition(m_position);
}

void CGuiOverlay::draw(sf::RenderTarget & target)
{
	target.draw(m_sprite);
}

int CGuiOverlay::getWidth() const
{
	return m_width;
}

int CGuiOverlay::getHeight() const
{
	return m_height;
}