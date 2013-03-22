#include "headers.h"

CScreenManager *CScreenManager::m_pInstance=NULL;

CScreenManager::CScreenManager()
{
    m_pInstance = this;

	m_curScreen = 0;
	gResources.setDefaultFont();

	windowWidth=800;
	windowHeight=600;
	windowTitle="BUGGED";
	style = 7;
	depthBuffer = 0;
	stencilBuffer = 0;
	antyaliasing = 0;
	framerateLimit = 60;

	m_game = new CGame();
	m_screens.push_back(m_game);

	m_inited = false;
}

void CScreenManager::run()
{
	if( !m_inited)
		m_Init();

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

void CScreenManager::m_Init()
{
	windowHeight = gSettings.GetBoosted<int>("WindowSize.height", 800);
	windowWidth = gSettings.GetBoosted<int>("WindowSize.width", 600);

	windowTitle = gSettings.GetBoosted<std::string>("WindowTitle.title", "LE BUGGED");
	
	style = gSettings.GetBoosted<int>("WindowSettings.style", 7);
	depthBuffer = gSettings.GetBoosted<int>("WindowSettings.depthBuffer", 0);
	stencilBuffer = gSettings.GetBoosted<int>("WindowSettings.stencilBuffer", 0);
	antyaliasing = gSettings.GetBoosted<int>("WindowSettings.antialiasing", 0);

	framerateLimit = gSettings.GetBoosted<int>("WindowSettings.framerateLimit", 60);

    window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Uint32(style), sf::ContextSettings(depthBuffer, stencilBuffer, antyaliasing) );
	window.setFramerateLimit(framerateLimit);

	m_inited = true;
}
