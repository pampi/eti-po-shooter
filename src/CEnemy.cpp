#include "headers.h"


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define M_PI 3.14159265358979323846f

#define MAXSPEED 1000.f
#define MINSPEED -1000.f


CEnemy::CEnemy() : CActor()
{

}

CEnemy::CEnemy(std::string pID, sf::Vector2f pPosition, State stan, enemyType type, float damage, float maxHp, float speed, float atackDistance, std::string spriteSheet, float pRotation /* =0.f */) : CActor(pID, pPosition, stan, maxHp, speed, pRotation)
{
	m_texture = std::make_shared<sf::Texture>(sf::Texture());
	m_texture->loadFromImage( *gResources.getImagePointer(spriteSheet) );


	#pragma region animacja
	m_ani_walkingU = new CAnimation();
	m_ani_walkingU->setSpriteSheet( *m_texture );
	m_ani_walkingU->addFrame( sf::IntRect(0 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(137 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(253 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(379 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(514 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(642 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(771 , 0, 110, 55) );
	m_ani_walkingU->addFrame( sf::IntRect(893 , 0, 110, 55) );


	m_ani_staying = new CAnimation();
	m_ani_staying->addFrame( sf::IntRect(0 , 0, 110, 60) );
	m_ani_staying->addFrame( sf::IntRect(137 , 0, 110, 60) );

	m_animationSprite = new CAnimatedSprite( sf::milliseconds(60) );
	m_animationSprite->setAnimation( *m_ani_walkingU );
	m_animationSprite->setPosition( m_position );
	m_animationSprite->setOrigin(sf::Vector2f(20,20));
#pragma endregion
	
	this->m_type = type;

	this->m_atackDistance = atackDistance;
	this->m_damage = damage;
	this->m_position = pPosition;
	this->m_alive = true;
	this->m_rotation = pRotation;

	fRect.width = (float)m_texture->getSize().x/10 -15;
	fRect.height = (float)m_texture->getSize().y-15;
	fRect.top = m_position.x;
	fRect.left = m_position.y;

	m_animationSprite->setScale(0.8f, 0.8f);

	m_shootDelay = 0.3f;

	cShape.setOrigin(30,30);
	cShape.setRadius(fRect.height/1.5f);
	cShape.setFillColor(sf::Color::Green);

	rShape.setSize(sf::Vector2f(fRect.width,fRect.height));
	rShape.setOrigin(30,30);
	rShape.setFillColor(sf::Color::Green);
}

void CEnemy::draw(sf::RenderTarget & target)
{
	target.draw(*m_animationSprite);
}

void CEnemy::update(sf::RenderWindow & App, sf::Time deltaTime)
{
	if( getHP() <= 0 )
	{
		m_alive = false;
	}

	if( isAlive() )
	{
		m_animationSprite->update(deltaTime);

		//##########################OBLICZ POZYCJE CELU###########################
		m_targetPos = gGame->getPlayer()->getPosition();

		if( CGame::findDistance(m_position, m_targetPos) <= m_atackDistance ) 
		{
			if( m_type == CEnemy::RANGE )
			{
				shoot(App);
			}

			if( m_state != CActor::WALKING_U )
			{
				m_state = CActor::WALKING_U;
			}

			m_xH = getPosition().x - m_targetPos.x;
			m_yH = getPosition().y - m_targetPos.y;
			m_rotation = (float)( atan2(m_yH, m_xH) * 180.f / M_PI + 180.f );

			m_dis.x = m_position.x - m_targetPos.x;
			m_dis.y = m_position.y - m_targetPos.y;

			DLen = sqrt(m_dis.x * m_dis.x + m_dis.y * m_dis.y);
			m_dis.x /= DLen;
			m_dis.y /= DLen;

			m_dis.x *= m_speed;
			m_dis.y *= m_speed;
			//########################################################################

			m_position = m_animationSprite->getPosition();

			m_animationSprite->move(-m_dis * deltaTime.asSeconds() );
			m_animationSprite->setRotation(m_rotation);

			fRect.top = m_animationSprite->getPosition().x - m_texture->getSize().x/2;
			fRect.left = m_animationSprite->getPosition().y - m_texture->getSize().y/2;

				
			rShape.setPosition(m_position.x,  m_position.y);	
			rShape.setRotation(m_rotation);
			//App.draw(rShape);

			
			cShape.setPosition(m_position.x,  m_position.y);
			//App.draw(cShape);
		}
		else
		{
			if( m_state != CActor::STAYING )
			{
				m_state = CActor::STAYING;
			}
		}
	}

}

bool CEnemy::isAlive() const
{
	return m_alive;
}

void CEnemy::shoot(sf::RenderWindow & App)
{
	if( m_shootClock.getElapsedTime().asSeconds() >= m_shootDelay )
	{
		gGame->mg_bulletsList.push_back( std::make_shared<CBullet>(CBullet(App, CBullet::NORMAL, CBullet::ENEMY, getPosition(), -m_rotation, (int)m_damage, 400.f)) );	
		
		//gGame->play("res/audio/shoot1.wav", false);
		m_shootClock.restart();
	}
}