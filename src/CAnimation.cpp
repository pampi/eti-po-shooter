#include "headers.h"

CAnimation::CAnimation() : m_texture(NULL)
{

}

void CAnimation::addFrame(sf::IntRect rect)
{
	m_frames.push_back( rect );
}

void CAnimation::setSpriteSheet(const sf::Texture &texturE)
{
	m_texture = &texturE;
}

const sf::Texture* CAnimation::getSpriteSheet() const
{
	return m_texture;
}

size_t CAnimation::getSize() const
{
	return m_frames.size();
}

const sf::IntRect &CAnimation::getFrame(size_t n) const
{
	return m_frames[n];
}