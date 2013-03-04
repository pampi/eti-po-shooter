#ifndef CMAINMENU_H
#define CMAINMENU_H


#include "headers.h"


class CMainMenu : public CScreen
{

public:
	CMainMenu();

	virtual int Step(sf::RenderWindow & App);

	bool m_inited;
	void m_Init();

	sf::Event m_event;

	sf::Text m_playText, m_exitText;
	sf::FloatRect m_playRect, m_exitRect;

	void m_drawMenuLables(sf::RenderWindow & App);
};
#endif