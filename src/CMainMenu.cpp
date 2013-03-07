#include "headers.h"

CMainMenu::CMainMenu()
{
	m_inited = false;
    gDDraw << "Omlet";
}

int CMainMenu::Step(sf::RenderWindow & App)
{
	while(true)
	{
		if(!m_inited)
		{
			m_Init();
		}

		while( App.pollEvent(m_event) )
		{
			if( m_event.type == sf::Event::Closed )
			{
				return -1; // wyjdz z gry(-1)
			}

			if( m_event.type == sf::Event::KeyPressed )
			{
				if( m_event.key.code == sf::Keyboard::Escape )
				{
					return -1; // wroc do menu(0), ale ze nie ma to wyjdz z gry(-1)
				}

			}

			if( m_event.type == sf::Event::MouseButtonPressed )
			{
				if( m_event.mouseButton.button == sf::Mouse::Left )
				{
					
				}
			}
		} // events loop

		App.clear();

		// J¥DRO MENU G£ÓWNEGO \|/

		//m_drawMenuLables(App);
		m_updateButtons(App);




		// J¥DRO MENU G£ÓWNEGO /|\


		// tak se mo¿esz tu wrzuciæ coœ co potrzebujesz zobaczyæ, albo ³aduj w loga
#if (DRAWDEBUG)
		gDDraw.add((int) gFPS.getFPS() ,"FPS: ");
		gDDraw.add("To jest menu glowne");
		gDDraw.draw(App);
#endif


		// ¯eby siê licznik fps aktualizowa³
		gFPS.update();

		// Sleep ¿eby proca nie katowa³o
		sf::sleep(sf::milliseconds(10));

		App.display();
	} // main loop

	return -1;
}

void CMainMenu::m_Init()
{
	gLogger << gLogger.LOG_WARNING <<  "initer main menu";


	m_loadButtons();



	m_inited = true;
}


void CMainMenu::m_loadButtons()
{
	// Tu musisz ogarn¹æ wczytanie z xml wszystkich plików, skonfigurowanie ich i wrzucenie do listy
	CMenuTextButton *lol = new CMenuTextButton(sf::Vector2f(100,100), 50U, sf::String("DUPA"), 2, sf::Color::Red, sf::Color::Green);
	lol->setFont( gResources.getFont() );
	m_buttons.push_back(lol);

	
	
}

void CMainMenu::m_updateButtons(sf::RenderWindow & App)
{
	for(std::list<class CTextButton*>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++)
	{

		(*it)->update(App);
		(*it)->draw(App);
	}
}
