#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "headers.h"

class CAnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	CAnimatedSprite(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);

	void update(sf::Time deltaTime);
	void setAnimation(const CAnimation &animation);
	void setFrameTime(sf::Time time);
	void play();
	void pause();
	void stop();
	void setLooped(bool looped);
	void setColor(const sf::Color &color);
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool isLooped() const;
	bool isPlaying() const;
	sf::Time getFrameTime() const;
	void setFrame(size_t newFrame, bool resetTime = true);

private:
	const CAnimation *m_animation;
	sf::Time m_frameTime;
	sf::Time m_currentTime;
	size_t m_currentFrame;
	bool m_isPaused;
	bool m_isLooped;
	const sf::Texture *m_texture;
	sf::Vertex m_vertices[4];

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif