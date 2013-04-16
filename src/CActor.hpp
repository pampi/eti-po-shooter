#ifndef CACTOR_H
#define CACTOR_H

#include "headers.h"

class CActor
{
public:
	enum State { NOPE, STAYING, WALKING_L, WALKING_R, WALKING_U, WALKING_D, SHOOTING, DYING, DEAD }; // dying - imies≥Ûw przymiotnikowy teraüniejszy czynny

	CActor()
	{
		m_id = "";
		m_position.x = 0;
		m_position.y = 0;
		m_state = CActor::NOPE;
		m_hp = 0;
	}
	CActor(std::string ID, sf::Vector2f position, State state, float hp)
	{
		m_id = ID;
		m_position = position;
		m_state = state;
		m_hp = hp;
	}
	virtual void draw(sf::RenderTarget & target)=0;
	virtual void update(sf::RenderWindow & App, sf::Time deltaTime)=0;
	~CActor() {};


    void setPosition( sf::Vector2f newPosition )
	{
		m_position = newPosition;
	}

    void setPosition( float x, float y )
	{
		m_position.x = x;
		m_position.y = y;
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

protected:
	std::string m_id;
	sf::Vector2f m_position;
	State m_state;
	float m_hp;
	sf::Texture *m_texture;

	class CAnimation *m_ani_walkingU, *m_ani_walkingD, *m_ani_walkingL, *m_ani_walkingR, *m_ani_staying, *m_ani_dying;
	class CAnimatedSprite *m_animationSprite;


};
#endif
