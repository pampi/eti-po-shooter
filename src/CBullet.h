#ifndef CBULLET_H
#define CBULLET_H


#include "headers.h"

class CBullet
{
public:
	CBullet();
	CBullet(sf::RenderWindow & App, sf::Vector2f StartPosition, float Rotation, int bulletDmg);

	void update(sf::RenderWindow & App, float deltaTime);

	bool toDelete() const;

	sf::Sprite m_sprite;
	//sf::Texture *m_texture;
	std::shared_ptr<sf::Texture> m_textureU;

	void setToDelete();

	int getBulletDamage() const;

	sf::FloatRect fRect;
	sf::CircleShape cShape;

	sf::Vector2f getPosition() const;

private:
	sf::Vector2f m_dis, m_startPos, m_mousePos;
	sf::Vector2i m_ImousePos;

	float m_rotation, m_vel, DLen, Dx,Dy;

	int m_damage, m_lifetime;

	bool m_toDelete;

};
#endif