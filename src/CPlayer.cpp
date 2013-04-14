#include "headers.h"


CPlayer::CPlayer() : CActor()
{

}

CPlayer::CPlayer(std::string ID, sf::Vector2f position, State state, float hp, std::string spriteSheet) : CActor(ID, position, state, hp)
{
	m_texture = new sf::Texture;
	m_texture->loadFromImage( gResources.getImage(spriteSheet) );

	m_ani_walkingD = new CAnimation();
	m_ani_walkingD->setSpriteSheet( *m_texture );
	m_ani_walkingD->addFrame( sf::IntRect(0 , 0 , 32, 48) );
	m_ani_walkingD->addFrame( sf::IntRect(32, 0 , 32, 48) );
	m_ani_walkingD->addFrame( sf::IntRect(64, 0 , 32, 48) );
	m_ani_walkingD->addFrame( sf::IntRect(96, 0 , 32, 48) );

	m_ani_walkingL = new CAnimation();
	m_ani_walkingL->setSpriteSheet( *m_texture );
	m_ani_walkingL->addFrame( sf::IntRect(0 , 48, 32, 48) );
	m_ani_walkingL->addFrame( sf::IntRect(32, 48, 32, 48) );
	m_ani_walkingL->addFrame( sf::IntRect(64, 48, 32, 48) );
	m_ani_walkingL->addFrame( sf::IntRect(96, 48, 32, 48) );

	m_ani_walkingR = new CAnimation();
	m_ani_walkingR->setSpriteSheet( *m_texture );
	m_ani_walkingR->addFrame( sf::IntRect(0 , 96, 32, 48) );
	m_ani_walkingR->addFrame( sf::IntRect(32, 96, 32, 48) );
	m_ani_walkingR->addFrame( sf::IntRect(64, 96, 32, 48) );
	m_ani_walkingR->addFrame( sf::IntRect(96, 96, 32, 48) );

	m_ani_walkingU = new CAnimation();
	m_ani_walkingU->setSpriteSheet( *m_texture );
	m_ani_walkingU->addFrame( sf::IntRect(0 , 144, 32, 48) );
	m_ani_walkingU->addFrame( sf::IntRect(32, 144, 32, 48) );
	m_ani_walkingU->addFrame( sf::IntRect(64, 144, 32, 48) );
	m_ani_walkingU->addFrame( sf::IntRect(96, 144, 32, 48) );

	m_ani_staying = new CAnimation();
	m_ani_staying->setSpriteSheet( *m_texture );
	m_ani_staying->addFrame( sf::IntRect(0 , 192, 32, 48) );
	m_ani_staying->addFrame( sf::IntRect(32, 192, 32, 48) );
	m_ani_staying->addFrame( sf::IntRect(64, 192, 32, 48) );
	m_ani_staying->addFrame( sf::IntRect(96, 192, 32, 48) );


	m_animationSprite = new CAnimatedSprite();
	m_animationSprite->setAnimation( *m_ani_staying );
	m_animationSprite->setPosition( m_position );
}

void CPlayer::update(sf::RenderWindow & App, sf::Time deltaTime)
{
	m_animationSprite->update( deltaTime );

	// elsy bo nie ma animacji poœrednich ani skoœnych
	// LEWO 
	if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::A) )
	{
		if( m_state != CActor::WALKING_L )
		{
			m_state = CActor::WALKING_L;
			m_animationSprite->setAnimation( *m_ani_walkingL );
		}
	}

	// PRAWO
	else if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::D) )
	{
		if( m_state != CActor::WALKING_R )
		{
			m_state = CActor::WALKING_R;
			m_animationSprite->setAnimation( *m_ani_walkingR );
		}
	}

	// DÓ£
	else if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::S) )
	{
		if( m_state != CActor::WALKING_D )
		{
			m_state = CActor::WALKING_D;
			m_animationSprite->setAnimation( *m_ani_walkingD );
		}
	}

	// GÓRA
	else if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::W) )
	{
		if( m_state != CActor::WALKING_U )
		{
			m_state = CActor::WALKING_U;
			m_animationSprite->setAnimation( *m_ani_walkingU );
		}
	}

	// STÓJ
	else if( CInputHandler::GetInstance()->isKeyPressed(sf::Keyboard::Space) )
	{
		if( m_state != CActor::STAYING )
		{
			m_state = CActor::STAYING;
			m_animationSprite->setAnimation( *m_ani_staying );
		}
	}

}

void CPlayer::draw(sf::RenderTarget & target)
{
	target.draw( *m_animationSprite );
}
