#include "CGame.h"

CGame::CGame()
{
	gDDraw << "Dupa";
	gLogger << gLogger.LOG_WARNING <<  "uops";
}

int CGame::Step(sf::RenderWindow & App)
{
	while(true)
	{
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
		} // events loop

		App.clear();

		// J�DRO GRY \|/


		// tak se mo�esz tu wrzuci� co� co potrzebujesz zobaczy�, albo �aduj w loga
#if (DRAWDEBUG)
		gDDraw.add((int) gFPS.getFPS() ,"FPS: ");
		gDDraw.draw(App);
#endif


		// �eby si� licznik fps aktualizowa�
		gFPS.update();

		// Sleep �eby proca nie katowa�o
		sf::sleep(sf::milliseconds(10));

		App.display();
	} // main loop
}