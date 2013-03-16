#ifndef CGAME_H
#define CGAME_H

#include "headers.h"

class CGame : public CScreen, public CScript
{
public:
	CGame();

	virtual int Step(sf::RenderWindow & App);

private:
	sf::Event m_event;

	bool m_inited;
	void m_Init();

	void manageButtons();
	void drawGui(sf::RenderWindow & App);

};
#endif
