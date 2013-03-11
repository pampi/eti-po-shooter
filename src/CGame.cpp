#include "headers.h"

CGame::CGame()
{
	m_inited = false;
	gDDraw << "Dupa";
	gLogger << gLogger.LOG_WARNING <<  "konstuktor game";
}

int CGame::Step(sf::RenderWindow & App)
{
	for(;;)
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
					return -1; // wyjdz z gry(-1)
				}

			
			}
		} // events loop

		App.clear();

		// J¥DRO GRY \|/

		drawGui(App);


		// J¥DRO GRY /|\

		// tak se mo¿esz tu wrzuciæ coœ co potrzebujesz zobaczyæ, albo ³aduj w loga
#if (DRAWDEBUG)
		gDDraw.add((int) gFPS.getFPS() ,"FPS: ");
		//gDDraw.add("To jest wlasciwa gra");
		gDDraw.draw(App);
#endif


		// ¯eby siê licznik fps aktualizowa³
		gFPS.update();

		// Sleep ¿eby proca nie katowa³o
		sf::sleep(sf::milliseconds(10));

		App.display();
	} // main loop
}

void CGame::m_Init()
{
	gLogger << gLogger.LOG_WARNING <<  "initer game";

	m_inited = true;
    // Laduj menu
    gResources.loadLevel(0);
}

void CGame::drawGui(sf::RenderTarget & App)
{
	for( std::list<class CGuiElement*>::iterator it = gResources.getGuiList()->begin(); it != gResources.getGuiList()->end(); it++ )
	{
		if(static_cast<class CButton*>(*it)->type == CGuiElement::GUI_BUTTON)
		{
			if( !static_cast<class CButton*>(*it)->isHidden() )
			{
				static_cast<class CButton*>(*it)->draw(App);
			}
		}
	}
}
