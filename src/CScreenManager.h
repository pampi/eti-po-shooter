#ifndef CSCREENMGR_H
#define CSCREENMGR_H

#include "headers.h"

class CScreenManager
{
public:
	CScreenManager();

	void run();

    class CGame *GetGame();
    static CScreenManager *GetInstance();

private:
	bool m_inited;
	void m_Init();

	sf::RenderWindow window;

	int m_curScreen;
	std::vector<CScreen*> m_screens;

	class CGame *m_game;

	// window settings
	int windowWidth, windowHeight;
	std::string windowTitle;
	int style, depthBuffer, stencilBuffer, antyaliasing, framerateLimit;


protected:
    static CScreenManager* m_pInstance;
	
};
#endif
