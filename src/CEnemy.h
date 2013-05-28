#ifndef CENEMY_H
#define CENEMY_H

#include "headers.h"


class CEnemy : public CActor
{
public:
	enum enemyType {MELEE, RANGE};
	CEnemy();
	CEnemy(std::string pID, sf::Vector2f pPosition, State stan, enemyType type, float damage, float maxHp, float speed, std::string spriteSheet, float rotation =0.f);


	virtual void draw(sf::RenderTarget & target);
	virtual void update(sf::RenderWindow & App, sf::Time deltaTime);

private:
	float m_damage;
	enemyType m_type;

};
#endif