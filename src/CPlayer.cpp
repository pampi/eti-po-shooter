#include "headers.h"


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define M_PI 3.14159265358979323846f

#define MAXSPEED 1000.f
#define MINSPEED -1000.f

#define MAXSTAMINA 200
#define STAMINAFACTORUP 2.f
#define STAMINAFACTORDOWN 4.f

CPlayer::CPlayer() : CActor()
{

}

CPlayer::CPlayer(std::string ID, sf::Vector2f position, State state, float hp, float speed, float rotation, std::string spriteSheet) : CActor(ID, position, state, hp, speed, rotation)
{
	//m_texture = new sf::Texture;
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


	m_dx = 0;
	m_dy = 0;

	fRect.width = fRect.height = 30;
	
	m_stamina = MAXSTAMINA;
	m_staminaClock.restart();

	m_shootDelay = 0.25f;
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

	 // GÓRA
	 if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::W) && !CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::LShift) )
	 {
		 //changePlayerState( CActor::WALKING_U );
		 m_newState = CActor::WALKING_U;
	 }
	 else
	 {
		 m_newState = CActor::STAYING;
	 }

	// DÓ£
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::S) )
	{
		//changePlayerState( CActor::WALKING_D );
		m_newState = CActor::WALKING_D;
	}

	// STÓJ
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::Space) )
	{
		//changePlayerState( CActor::STAYING );
		m_newState = CActor::STAYING;
    }

	// STRZEL
	if( CInputHandler::GetInstance()->isButtonPressed(sf::Mouse::Left) )
	{
		shoot(App);
	}

	// SPRINT
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::LShift) && CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::W) )
	{
		m_newState = CActor::RUNNING;
	}

	//SKILL 1
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::Num1) )
	{
		if( activSkill != CActor::SINGLE_SHOOTING )
			activSkill = CActor::SINGLE_SHOOTING;
	}

	//SKILL 2
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::Num2) )
	{
		if( activSkill != CActor::TRIPLE_SHOOTING )
			activSkill = CActor::TRIPLE_SHOOTING;
	}

	//SKILL 3
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::Num3) )
	{
		if( activSkill != CActor::BIG_SHOOTING )
			activSkill = CActor::BIG_SHOOTING;
	}

	// STAMINA GRACZA
	if( m_stamina <= 0 )
	{
		m_newState = CActor::WALKING_U;
	}

	changePlayerState(m_newState);

	updateStamina();

//#################################################################################	

	if( m_speed > MAXSPEED )
		m_speed = MAXSPEED;

	if( m_speed < MINSPEED )
		m_speed = MINSPEED;

	if(m_rotation > 359)
		m_rotation = 0;

	if(m_rotation < 0)
		m_rotation = 359;


	m_ImousePos = sf::Mouse::getPosition(App);
	m_mousePos = App.mapPixelToCoords(m_ImousePos);

	m_xH = getPosition().x - m_mousePos.x;
	m_yH = getPosition().y - m_mousePos.y;
	m_gunRotate = (float)( atan2(m_yH, m_xH) * 180.f / M_PI + 180.f );

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
//################################################################################


	// sprawdzanie kolizji ze œcianami
	std::vector<CollisionObject*> odp = gGame->collisionTree->getObjectsAt( m_position.x  -15.0f,  m_position.y -15.0f  );
	BOOST_FOREACH(CollisionObject* obj, odp)
	{
		if( obj->typ == CollisionObject::WALL )
		{
			if( fRect.intersects( obj->fRect ) )
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
	}
	
	m_animationSprite->setPosition(m_position);

	// just 4 debug
	gDDraw.add(m_animationSprite->getPosition().x, "X: ");
	gDDraw.add(m_animationSprite->getPosition().y, "Y: ");
	//gDDraw.add(m_dx, "dX: ");
	//gDDraw.add(m_dy, "dY: ");
	gDDraw.add(m_position.x, "mX: ");
	gDDraw.add(m_position.y, "mY: ");
	gDDraw.add((int)gGame->mg_bulletsList.size(), "Bullets: ");


}

void CPlayer::updatePosition()
{
    m_animationSprite->setPosition(m_position);
}

void CPlayer::draw(sf::RenderTarget & target)
{
	target.draw( *m_animationSprite );
}

void CPlayer::shoot(sf::RenderWindow & App)
{
	if( m_shootClock.getElapsedTime().asSeconds() >= m_shootDelay )
	{
		if( activSkill == CActor::SINGLE_SHOOTING )
		{
			gGame->mg_bulletsList.push_back( std::make_shared<CBullet>(CBullet(App, CBullet::NORMAL, getPosition(), -m_gunRotate, 50)) );
			gGame->bulletCounter++;
		}
		else if( activSkill == CActor::BIG_SHOOTING )
		{
			if( m_stamina >= 10.f )
			{
				gGame->mg_bulletsList.push_back( std::make_shared<CBullet>(CBullet(App, CBullet::BIG, getPosition(), -m_gunRotate, 50)) );
				gGame->bulletCounter++;
				m_stamina -= 10.f;
			}
		}
		else if( activSkill == CActor::TRIPLE_SHOOTING )
		{
			if( m_stamina >= 20.f )
			{
				sf::Vector2f bPos = getPosition();
				gGame->mg_bulletsList.push_back( std::make_shared<CBullet>(CBullet(App, CBullet::NORMAL, bPos, -m_gunRotate, 50)) );
				bPos.x += 30;
				bPos.y += 30;
				gGame->mg_bulletsList.push_back( std::make_shared<CBullet>(CBullet(App, CBullet::NORMAL, bPos, -m_gunRotate, 50)) );
				bPos.x -= 60;
				bPos.y -= 60;
				gGame->mg_bulletsList.push_back( std::make_shared<CBullet>(CBullet(App, CBullet::NORMAL, bPos, -m_gunRotate, 50)) );
				gGame->bulletCounter += 3;
				m_stamina -= 20.f;
			}
		}
		
		m_shootClock.restart();
	}
	
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

	case CActor::RUNNING :
		{
			if( m_state != CActor::RUNNING )
			{
				m_state = CActor::RUNNING;
				m_animationSprite->setAnimation( *m_ani_staying );
				m_animationSprite->setFrameTime( sf::milliseconds(20) );
				m_speed = 300.f;
			}
			
			break;
		}

	}
}

void CPlayer::updateStamina()
{
	if( m_state == CActor::RUNNING )
	{
		if( m_staminaClock.getElapsedTime().asSeconds() >= 0.5f )
		{
			m_stamina -= STAMINAFACTORDOWN;
			if( m_stamina < 0)
				m_stamina = 0;

			m_staminaClock.restart();
		}
	}
	else
	{
		if( m_staminaClock.getElapsedTime().asSeconds() >= 1.0f )
		{
			m_stamina += STAMINAFACTORUP;

			if( m_stamina > MAXSTAMINA)
				m_stamina = MAXSTAMINA;

			m_staminaClock.restart();
		}
	}
}

float CPlayer::getPercentStamina() const
{
	return m_stamina / MAXSTAMINA * 100.f;
}

float CPlayer::getStamina() const
{
	return m_stamina;
}

void CPlayer::setStamina(float newStamina)
{
	m_stamina = newStamina;
}