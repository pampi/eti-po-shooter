#include "headers.h"

CScreenManager::CScreenManager()
{
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
    gLogger << CLogger::LOG_INFO << "CScreenManager konstruktor";
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

class CGame *CScreenManager::GetGame()
{
    return m_game;
}

void CScreenManager::m_Init()
{
    windowHeight = gSettings.Get<int>("WindowSize.height", 800);
    windowWidth = gSettings.Get<int>("WindowSize.width", 600);

    windowTitle = gSettings.Get<std::string>("WindowTitle.title", "LE BUGGED");
	
    style = gSettings.Get<int>("WindowSettings.style", 7);
    depthBuffer = gSettings.Get<int>("WindowSettings.depthBuffer", 0);
    stencilBuffer = gSettings.Get<int>("WindowSettings.stencilBuffer", 0);
    antyaliasing = gSettings.Get<int>("WindowSettings.antialiasing", 0);

    framerateLimit = gSettings.Get<int>("WindowSettings.framerateLimit", 60);

    window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Uint32(style), sf::ContextSettings(depthBuffer, stencilBuffer, antyaliasing) );
	window.setFramerateLimit(framerateLimit);

	m_inited = true;
}
