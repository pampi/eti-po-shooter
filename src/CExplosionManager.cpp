#include "headers.h"


CExplosionManager::CExplosionManager()
{
	m_texture = std::make_shared<sf::Texture>(sf::Texture());
	m_texture->loadFromImage( *gResources.getImagePointer("res/img/smokeSheet2.png") );

#pragma region animacja

	m_explosionAnimation = new CAnimation();
	m_explosionAnimation->setSpriteSheet( *m_texture );
	m_explosionAnimation->addFrame(sf::IntRect(0, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(37, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(75, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(112, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(150, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(187, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(225, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(262, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(300, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(337, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(375, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(412, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(450, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(487, 0, 30, 34));
	m_explosionAnimation->addFrame(sf::IntRect(520, 0, 30, 34));
#pragma endregion
}

void CExplosionManager::addExplosion(sf::Vector2f position)
{
	std::shared_ptr<CAnimatedSprite> sprite = std::make_shared<CAnimatedSprite>( CAnimatedSprite(sf::milliseconds(80), false, false) );
	sprite->setAnimation( *m_explosionAnimation );
	sprite->setOrigin(15.f,15.f);
	sprite->setPosition(position);

	m_animationList.push_back( sprite );
}

void CExplosionManager::updateExplosion(sf::RenderWindow & App, sf::Time deltaTime)
{
	for(std::list< std::shared_ptr<class CAnimatedSprite> >::iterator it = m_animationList.begin(); it != m_animationList.end(); )
	{
		if( (*it)->isPlaying() )
		{
			(*it)->update(deltaTime);
			App.draw( *(*it) );
			it++;
		}
		else
		{
			it = m_animationList.erase(it);
		}
	}
}