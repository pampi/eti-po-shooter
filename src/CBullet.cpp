#include "headers.h"


CBullet::CBullet(sf::RenderWindow & App, bulletType bType, sf::Vector2f pStartPosition, float pRotation, int pBulletDmg)
{
	m_vel = 700.f;
	m_lifetime = 0;
	m_damage = pBulletDmg;
	m_type = bType;

	this->m_startPos = pStartPosition;
	this->m_toDelete = false;
	this->m_rotation = pRotation;

	m_ImousePos = sf::Mouse::getPosition(App);
	m_mousePos = App.mapPixelToCoords(m_ImousePos);
		
	m_dis.x = m_startPos.x - m_mousePos.x;
	m_dis.y = m_startPos.y - m_mousePos.y;

	DLen = sqrt(m_dis.x * m_dis.x + m_dis.y * m_dis.y);
	m_dis.x /= DLen;
	m_dis.y /= DLen;

	m_dis.x *= m_vel;
	m_dis.y *= m_vel;


	m_textureU = std::make_shared<sf::Texture>(sf::Texture());

	if( m_type == NORMAL )
	{
		m_textureU->loadFromImage( *gResources.getImagePointer("res/img/bullet1.png") );
	}

	if( m_type == BIG )
	{
		m_textureU->loadFromImage( *gResources.getImagePointer("res/img/bullet2.png") );
	}
	

	m_sprite.setTexture( *m_textureU );
	m_sprite.setOrigin( (float)m_textureU->getSize().x /2, (float)m_textureU->getSize().y /2);
	m_sprite.setPosition(m_startPos);
	m_sprite.setRotation(-m_rotation);

	fRect.width = (float)m_textureU->getSize().x-10;
	fRect.height = (float)m_textureU->getSize().y-10;
	fRect.top = m_startPos.x;
	fRect.left = m_startPos.y;

	cShape.setFillColor(sf::Color::Yellow);
	cShape.setRadius((float)(m_textureU->getSize().x-10));
	cShape.setOrigin(cShape.getRadius()/2, cShape.getRadius()/2 );
	cShape.setPosition(m_startPos);
}

void CBullet::update(sf::RenderWindow & App, float deltaTime)
{
	if( m_lifetime < 200 && !m_toDelete )
	{
		m_sprite.move(-m_dis * deltaTime);
		fRect.top = m_sprite.getPosition().x - m_textureU->getSize().x/2;
		fRect.left = m_sprite.getPosition().y - m_textureU->getSize().y/2;
		App.draw( m_sprite );
		m_lifetime++;

		cShape.setPosition(fRect.top,  fRect.left);
		//gDDraw.add(fRect.top, "top: ");
		//gDDraw.add(fRect.left, "left: ");
		//App.draw(cShape);

		
	}
	else
	{
		m_toDelete = true;
	}
	
}

bool CBullet::toDelete() const
{
	return m_toDelete;
}

void CBullet::setToDelete()
{
	m_toDelete = true;
}

int CBullet::getBulletDamage() const
{
	return m_damage;
}

sf::Vector2f CBullet::getPosition() const
{
	return m_sprite.getPosition();
}