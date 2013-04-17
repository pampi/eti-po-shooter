﻿#ifndef CGAME_H
#define CGAME_H

#include "headers.h"

class CGame : public CScreen, public CScript, public CSoundManager
{
public:
	CGame();

	virtual int Step(sf::RenderWindow & App);

private:
	sf::Event m_event;

    time_t m_lastEventTime;
    bool m_idle;

	bool m_inited;
	void m_Init();

	void manageButtons();
	void drawGui(sf::RenderWindow & App);

	sf::Time m_deltaTime;
	sf::Clock m_deltaClock;

	class CPlayer *m_player;
};
#endif