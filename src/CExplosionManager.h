#ifndef CExplosionManager_H
#define CExplosionManager_H

#include "headers.h"

class CExplosionManager
{
public:
	CExplosionManager();

	void addExplosion(sf::Vector2f position);

	void updateExplosion(sf::RenderWindow & App, sf::Time deltaTime);

private:
	std::list< std::shared_ptr<class CAnimatedSprite> > m_animationList;

	class CAnimation *m_explosionAnimation;

	sf::Vector2f m_position;

	std::shared_ptr<sf::Texture> m_texture;
};
#endif