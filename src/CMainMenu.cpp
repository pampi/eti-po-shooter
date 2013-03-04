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
					if( m_playRect.contains((float)m_event.mouseButton.x, (float)m_event.mouseButton.y) )
					{
						return 1; // Zacznij grac
					}

					if( m_exitRect.contains((float)m_event.mouseButton.x, (float)m_event.mouseButton.y) )
					{
						return -1; // Wyjdz z gry
					}
				}
			}
		} // events loop

		App.clear();

		// J¥DRO MENU G£ÓWNEGO \|/

		m_drawMenuLables(App);





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


	m_playText.setFont( gResources.getFont() );
	m_playText.setString( sf::String("Start Game") );
	m_playText.setColor( sf::Color(255,0,0,255) );
	m_playText.setCharacterSize(80U);
	m_playText.setPosition( 400, 200);

	m_exitText.setFont( gResources.getFont() );
	m_exitText.setString( sf::String("Exit Game") );
	m_exitText.setColor( sf::Color(255,0,0,255) );
	m_exitText.setCharacterSize(80U);
	m_exitText.setPosition( 400, 300);

	m_playRect = m_playText.getGlobalBounds();
	m_exitRect = m_exitText.getGlobalBounds();


	m_inited = true;
}

void CMainMenu::m_drawMenuLables(sf::RenderWindow & App)
{
	if( m_playRect.contains( (float)sf::Mouse::getPosition(App).x, (float)sf::Mouse::getPosition(App).y) )
	{
		m_playText.setColor( sf::Color(0,255,0,255) );
	}
	else
	{
		m_playText.setColor( sf::Color(255,0,0,255) );
	}

	if( m_exitRect.contains( (float)sf::Mouse::getPosition(App).x, (float)sf::Mouse::getPosition(App).y) )
	{
		m_exitText.setColor( sf::Color(0,255,0,255) );
	}
	else
	{
		m_exitText.setColor( sf::Color(255,0,0,255) );
	}


	App.draw(m_playText);
	App.draw(m_exitText);
}