#ifndef CPLAYER_H
#define CPLAYER_H

#include "headers.h"

class CPlayer : public CActor, public TSingleton<CPlayer>
{
public:
	CPlayer();
	CPlayer(std::string ID, sf::Vector2f position, State state, float hp, std::string spriteSheet);


	void draw(sf::RenderTarget & target);
	void update(sf::RenderWindow & App, sf::Time deltaTime);
	
    void updatePosition();

    void setState(CActor::State newState);

private:


};
#endif
