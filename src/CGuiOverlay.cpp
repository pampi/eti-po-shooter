#include "headers.h"

CGuiOverlay::CGuiOverlay(sf::Vector2f position, std::string ID, int pheight, int pwidth, bool hide, bool active,  std::string imgPathNormal, std::string imgPathActive) : CGuiElement(CGuiElement::GUI_STATIC_OVERLAY ,position, ID, hide)
{
	m_imgPathNormal = imgPathNormal;
	m_imgPathActive = imgPathActive;
	m_width = pwidth;
	m_height = pheight;
	m_active = active;

	m_textureP = std::make_shared<sf::Texture>( sf::Texture() );
	m_textureP->loadFromImage( *gResources.getImagePointer(imgPathNormal) );
	m_sprite.setTexture( *m_textureP );
	m_sprite.setPosition(m_position);

	setActive(m_active);
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

void CGuiOverlay::setActive(bool trueORfalse)
{
	m_active = trueORfalse;
	if( trueORfalse )
	{
		m_textureP->loadFromImage( *gResources.getImagePointer(m_imgPathActive) );
		m_sprite.setTexture( *m_textureP );
	}
	else
	{
		m_textureP->loadFromImage( *gResources.getImagePointer(m_imgPathNormal) );
		m_sprite.setTexture( *m_textureP );
	}
}

bool CGuiOverlay::isActive() const
{
	return m_active;
}