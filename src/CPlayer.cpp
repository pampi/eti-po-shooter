#include "headers.h"

#define MAXSPEED 1000.f
#define MINSPEED -1000.f
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define M_PI 3.14159265358979323846f

CPlayer::CPlayer() : CActor()
{

}

CPlayer::CPlayer(std::string ID, sf::Vector2f position, State state, float hp, float speed, float rotation, std::string spriteSheet) : CActor(ID, position, state, hp, speed, rotation)
{
	m_texture = new sf::Texture;
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


	m_dx = 0;
	m_dy = 0;

	fRect.width = fRect.height = 30;
	
	
}

void CPlayer::update(sf::RenderWindow & App, sf::Time deltaTime)
{
	m_animationSprite->update( deltaTime );
	m_prevPositon = m_position;

	// LEWO 
    if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::A) )
	{
			m_rotation += ((-170.0f) * static_cast<float>( deltaTime.asSeconds() ));
			m_animationSprite->setRotation(m_rotation);
	}

	// PRAWO
	 if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::D) )
	{
			m_rotation +=  (170.0f * static_cast<float>( deltaTime.asSeconds() ));
			m_animationSprite->setRotation(m_rotation);
	}

	// DÓ£
	 if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::S) )
	{
		changePlayerState( CActor::WALKING_D );
	}

	// GÓRA
	 if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::W) )
	{
		changePlayerState( CActor::WALKING_U );
	}

	// STÓJ
	 if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::Space) )
	{
		changePlayerState( CActor::STAYING );
    }

	if( m_speed > MAXSPEED )
		m_speed = MAXSPEED;

	if( m_speed < MINSPEED )
		m_speed = MINSPEED;

	if(m_rotation > 359)
		m_rotation = 0;

	if(m_rotation < 0)
		m_rotation = 359;


	m_dx += m_speed * cos((m_rotation*M_PI)/180);
	m_dy += m_speed * sin((m_rotation*M_PI)/180);

	
	if( m_dx >= 1 || m_dx <= - 1 )
	{ 
		m_position.x += (int)(m_dx) * deltaTime.asSeconds();
		m_dx = m_dx - (int)(m_dx);
	}
	if( m_dy >= 1 || m_dy <= - 1 )
	{ 
		m_position.y += (int)(m_dy) * deltaTime.asSeconds();
		m_dy = m_dy - (int)(m_dy);
	}

	fRect.left = m_position.x -15.0f;
	fRect.top = m_position.y -15.0f;

	std::vector<CollisionObject*> odp = gGame->collisionTree->getObjectsAt( m_position.x  -15.0f,  m_position.y -15.0f  );
	BOOST_FOREACH(CollisionObject* obj, odp)
	{
		if( fRect.intersects( obj->rect ) )
		{
			m_position = m_prevPositon;

			changePlayerState( CActor::STAYING );

			sf::RectangleShape pshape;
			pshape.setSize(sf::Vector2f(30,30));
			pshape.setPosition(m_position.x -15.0f,  m_position.y -15.0f);
			pshape.setFillColor(sf::Color::Red);
			App.draw(pshape);

			break;
		}
	}
	
	m_animationSprite->setPosition(m_position);

	// just 4 debug
	gDDraw.add(m_animationSprite->getPosition().x, "X: ");
	gDDraw.add(m_animationSprite->getPosition().y, "Y: ");
	gDDraw.add(m_dx, "dX: ");
	gDDraw.add(m_dy, "dY: ");
	gDDraw.add(m_position.x, "mX: ");
	gDDraw.add(m_position.y, "mY: ");

}

void CPlayer::updatePosition()
{
    m_animationSprite->setPosition(m_position);
}

void CPlayer::draw(sf::RenderTarget & target)
{
	target.draw( *m_animationSprite );
}

void CPlayer::changePlayerState(CActor::State stan)
{
	switch(stan)
	{
	case CActor::WALKING_D :
		{
			if( m_state != CActor::WALKING_D )
			{
				m_state = CActor::WALKING_D;
				m_animationSprite->setAnimation( *m_ani_walkingU );
				m_animationSprite->setFrameTime( sf::milliseconds(50) );
				m_speed = -100.f;
			}
			break;
		}

	case CActor::WALKING_U :
		{
			if( m_state != CActor::WALKING_U )
			{
				m_state = CActor::WALKING_U;
				m_animationSprite->setAnimation( *m_ani_walkingU );
				m_animationSprite->setFrameTime( sf::milliseconds(50) );
				m_speed = 100.f;
			}
			break;
		}

	case CActor::STAYING :
		{
			if( m_state != CActor::STAYING )
			{
				m_state = CActor::STAYING;
				m_animationSprite->setAnimation( *m_ani_staying );
				m_animationSprite->setFrameTime( sf::milliseconds(300) );
				m_speed = 0.f;
			}
			m_speed = 0.f;

			break;
		}

	}
}