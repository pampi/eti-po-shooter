#ifndef CANIMATION_H
#define CANIMATION_H

#include "headers.h"

class CAnimation
{
public:
	CAnimation();

	void addFrame(sf::IntRect rect);
	void setSpriteSheet(const sf::Texture &texture);
	const sf::Texture *getSpriteSheet() const;
	size_t getSize() const;
	const sf::IntRect &getFrame(size_t n) const;

private:
	std::vector<sf::IntRect> m_frames;
	const sf::Texture *m_texture;

};
#endif