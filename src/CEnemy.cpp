#include "headers.h"


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define M_PI 3.14159265358979323846f

#define MAXSPEED 1000.f
#define MINSPEED -1000.f


CEnemy::CEnemy() : CActor()
{

}

CEnemy::CEnemy(std::string pID, sf::Vector2f pPosition, State stan, enemyType type, float damage, float maxHp, float speed, std::string spriteSheet, float rotation /* =0.f */) : CActor(pID, pPosition, stan, maxHp, speed, rotation)
{
	m_texture = std::make_shared<sf::Texture>(sf::Texture());
	m_texture->loadFromImage( *gResources.getImagePointer(spriteSheet) );


	#pragma region animacja
	m_ani_walkingU = new CAnimation();
	m_ani_walkingU->setSpriteSheet( *m_texture );
	m_ani_walkingU->addFrame( sf::IntRect(0 , 0, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(50 , 0, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(100 , 0, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(150 , 0, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(0 , 50, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(50 , 50, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(100 , 50, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(150 , 50, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(0 , 100, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(50 , 100, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(100 , 100, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(150 , 100, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(0 , 150, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(50 , 150, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(100 , 150, 50, 50) );
	m_ani_walkingU->addFrame( sf::IntRect(150 , 150, 50, 50) );


	m_ani_staying = new CAnimation();
	m_ani_staying->setSpriteSheet( *m_texture );
	m_ani_staying->addFrame( sf::IntRect(0 , 150, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(0 , 150, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(50 , 150, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(50 , 150, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(50, 50, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(50, 50, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(0, 50, 50, 50) );
	m_ani_staying->addFrame( sf::IntRect(0, 50, 50, 50) );

	m_animationSprite = new CAnimatedSprite( sf::milliseconds(300) );
	m_animationSprite->setAnimation( *m_ani_staying );
	m_animationSprite->setPosition( m_position );
	m_animationSprite->setOrigin(sf::Vector2f(25,25));
#pragma endregion







}

void CEnemy::draw(sf::RenderTarget & target)
{
	target.draw(*m_animationSprite);
}

void CEnemy::update(sf::RenderWindow & App, sf::Time deltaTime)
{

}