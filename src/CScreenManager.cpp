#include "headers.h"

CScreenManager::CScreenManager()
{
	m_curScreen = 0;

	window.create(sf::VideoMode(1280, 720), "Nobody expects...");

	m_game = new CGame();
	gResources.setDefaultFont();


	m_screens.push_back(m_game);
}

void CScreenManager::run()
{
	while( m_curScreen >= 0 )
	{
		m_curScreen = m_screens[m_curScreen]->Step(window);
	}
}