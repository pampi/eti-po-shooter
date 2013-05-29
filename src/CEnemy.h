#ifndef CENEMY_H
#define CENEMY_H

#include "headers.h"


class CEnemy : public CActor
{
public:
	enum enemyType {MELEE, RANGE};
	CEnemy();
	CEnemy(std::string pID, sf::Vector2f pPosition, State stan, enemyType type, float damage, float maxHp, float speed, float atackDistance, std::string spriteSheet, float rotation = 0.f);


	virtual void draw(sf::RenderTarget & target);
	virtual void update(sf::RenderWindow & App, sf::Time deltaTime);

	bool isAlive() const;
	float getDamage() const;

	sf::CircleShape cShape;
	sf::RectangleShape rShape;
	
	enemyType m_type;

private:
	float m_dx, m_dy, m_xH, m_yH;
	float m_damage, DLen, m_atackDistance;
	
	sf::Vector2f m_targetPos, m_dis;
	bool m_alive;

	float m_shootDelay;
	sf::Clock m_shootClock;

	void shoot(sf::RenderWindow & App);
};
#endif