#ifndef CACTOR_H
#define CACTOR_H

#include "headers.h"

class CActor
{
public:
	enum State { NOPE, STAYING, WALKING_L, WALKING_R, WALKING_U, WALKING_D, SHOOTING, DYING, DEAD }; // dying - imies³ów przymiotnikowy teraŸniejszy czynny

	CActor() : m_animationSprite(NULL)
	{
		m_id = "";
		m_position.x = 0;
		m_position.y = 0;
		m_state = CActor::NOPE;
		m_hp = 0;
		m_speed = 0;
		m_rotation = 0;
	}
	CActor(std::string ID, sf::Vector2f position, State state, float hp, float speed, float rotation) : m_animationSprite(NULL)
	{
		m_id = ID;
		m_position = position;
		m_state = state;
		m_hp = hp;
		m_speed = speed;
		m_rotation = rotation;
	}
	virtual void draw(sf::RenderTarget & target)=0;
	virtual void update(sf::RenderWindow & App, sf::Time deltaTime)=0;
	virtual ~CActor() {};


    void setPosition( sf::Vector2f newPosition )
	{
		m_position = newPosition;
		if (m_animationSprite)
		{
			m_animationSprite->setPosition(newPosition);
		}
		
	}

	void setRotation( float newRotation )
	{
		m_rotation = newRotation;
		if (m_animationSprite)
		{
			m_animationSprite->setRotation(m_rotation);
		}
	}

	float getRotation() const
	{
		return m_rotation;
	}

    void setPosition( float x, float y )
	{
		m_position.x = x;
		m_position.y = y;
		if (m_animationSprite)
		{
			m_animationSprite->setPosition(m_position);
		}
	}

	sf::Vector2f getPosition() const
	{
		return m_position;
	}

	float getHP() const
	{
		return m_hp;
	}

	void setHP(float newHP)
	{
		m_hp = newHP;
	}

	State getState() const
	{
		return m_state;
	}

	void setState( State newState )
	{
		m_state = newState;
	}

	std::string getID() const
	{
		return m_id;
	}

	void setID(std::string newID)
	{
		m_id = newID;
	}

	sf::FloatRect fRect;

protected:
	std::string m_id;
	sf::Vector2f m_position, m_prevPositon;
	State m_state;
	float m_hp;
	sf::Texture *m_texture;
	float m_speed;
	float m_rotation;

	class CAnimation *m_ani_walkingU, *m_ani_walkingD, *m_ani_walkingL, *m_ani_walkingR, *m_ani_staying, *m_ani_dying;
	class CAnimatedSprite *m_animationSprite;


};
#endif
