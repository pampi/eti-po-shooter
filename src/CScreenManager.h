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
	sf::RenderWindow window;

	int m_curScreen;

	std::vector<CScreen*> m_screens;

	class CGame *m_game;

protected:
    static CScreenManager* m_pInstance;
	
};
#endif
