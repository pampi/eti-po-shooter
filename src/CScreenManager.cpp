#include "headers.h"

CScreenManager *CScreenManager::m_pInstance=NULL;

CScreenManager::CScreenManager()
{
    m_pInstance = this;

	m_curScreen = 0;
	gResources.setDefaultFont();

	window.create(sf::VideoMode(1280, 720), "Nobody expects...");
	window.setFramerateLimit(60U);

	m_game = new CGame();


	m_screens.push_back(m_game);
}

void CScreenManager::run()
{
	while( m_curScreen >= 0 )
	{
		m_curScreen = m_screens[m_curScreen]->Step(window);
	}
}

CScreenManager *CScreenManager::GetInstance()
{
    if(!m_pInstance) m_pInstance = new CScreenManager();
    return m_pInstance;
}

class CGame *CScreenManager::GetGame()
{
    return m_game;
}
