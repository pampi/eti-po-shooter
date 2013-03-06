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


private:
	std::list<class CTextButton*> m_buttons;

	void m_loadButtons();
	void m_updateButtons(sf::RenderWindow & App);
};
#endif