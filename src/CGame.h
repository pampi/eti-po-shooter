#ifndef CGAME_H
#define CGAME_H

#include "headers.h"

class CGame : public CScreen
{
public:
	CGame();

	virtual int Step(sf::RenderWindow & App);

private:
	sf::Event m_event;

	bool m_inited;
	void m_Init();

};
#endif