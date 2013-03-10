#ifndef CSCREENMGR_H
#define CSCREENMGR_H

#include "headers.h"

class CScreenManager
{
public:
	CScreenManager();

	void run();

private:
	sf::RenderWindow window;

	int m_curScreen;

	std::vector<CScreen*> m_screens;

	class CGame *m_game;


	
};
#endif