#include "headers.h"

#define TIME_TO_IDLE 5

extern const char *strKey[];

CGame::CGame()
{
	m_inited = false;
    m_idle = false;
    m_lastEventTime = time(NULL);
    gLogger << CLogger::LOG_INFO << "CGame constructor";
	m_view = new sf::View(sf::FloatRect(0,0,1280,720));

	gameState = PLAYING;
	collisionTree = NULL;
}

CGame::~CGame()
{
	gLogger << CLogger::LOG_INFO << "CGame destructor";
}

CPlayer* CGame::getPlayer()
{
	return m_player;
}

int CGame::Step(sf::RenderWindow & App)
{
	for(;;)
	{
		if(!m_inited)
		{
			m_Init(App);
		}

		while( App.pollEvent(m_event) )
        {
            if(m_idle)
            {
                m_idle = false;
                callScriptFunction("stopIdleAction");
            }

            m_lastEventTime = time(NULL);

			if( m_event.type == sf::Event::Closed )
			{
				return -1; // wyjdz z gry(-1)
            }

            if( m_event.type == sf::Event::KeyPressed )
            {
                if( CInputHandler::GetInstance()->isToggled(CInputHandler::Escape) )
                {
                    return -1; // wyjdz z gry(-1)
                }

            }
		} // events loop

		// clear window
		App.clear();



		// tick timer
		m_deltaTime = m_deltaClock.restart();

		#pragma region IDLE
		//jeśli IDLE
        if(time(NULL)>m_lastEventTime+TIME_TO_IDLE)
        {
            gameState = CGame::IDLE;
        }
		#pragma endregion


		manageGameStates(App);

		

	
		// Rysuj DebugDraw
        gDDraw.add((int) gFPS.getFPS() ,"FPS: ");
        gDDraw.draw(App);

		// Żeby się licznik fps aktualizował
        gFPS.update();

		// Sleep żeby proca nie katowało
		sf::sleep(sf::milliseconds(10));

		App.display();
	} // main loop
}

void CGame::m_Init(sf::RenderWindow & App)
{
	m_inited = true;

    // Laduj poziom
    gResources.loadLevel(0);

	m_player = new CPlayer("1", gResources.loadPlayerStartPosition(), CActor::STAYING, 100.f, 0.f, 0.f, "res/img/dude.png");
    

	// tu by trzeba było podawać rozmiary całej mapy a nie tylko ekranu // TO DO
	//collisionTree = new CQuadTree(0, 0, 2000, 1000, 0, 5);

}

void CGame::drawGui(sf::RenderWindow & App)
{
    for( std::list<class CGuiElement*>::iterator it = gResources.m_guiElements.begin(); it != gResources.m_guiElements.end(); it++ )
	{
        switch((*it)->type)
        {
            case CGuiElement::GUI_BUTTON:
                {
                    CButton *btn=static_cast<CButton *>(*it);
                    if( !btn->isHidden() )
                    {
                        btn->update(App);
                        btn->draw(App);
                    }
                }
                break;

            case CGuiElement::GUI_TEXTBOX:
                {
                    CTextBox *textbox=static_cast<CTextBox *>(*it);
                    if( !textbox->isHidden() )
                    {
                        textbox->draw(App);
                    }
                }
                break;

            case CGuiElement::GUI_TIMED_TEXTBOX:
                {
                    CTimedTextBox *timedTextBox = static_cast<CTimedTextBox *>(*it);
                    timedTextBox->draw(App);
                }
                break;

            default:
                break;
        }
	}

	manageButtons();
}

void CGame::manageButtons()
{
    for( std::list<class CButton*>::iterator it = gButtonClicked.begin(); it != gButtonClicked.end();  )
	{
		CButton *btn=static_cast<CButton *>(*it);
		if(btn->type == CGuiElement::GUI_BUTTON)
		{
			if( !btn->isHidden() )
			{
				if( btn->wasClicked() )
				{
					// deal with ur button
                    // perform action
                    callScriptFunction(btn->getAction()->c_str());

                    if( !gButtonClicked.empty() )
                    {
                        // stop dealing
                        btn->resetState();
                        it = gButtonClicked.erase(it);
                    }
                    else
                    {
                        break;
                    }
				}
				else
				{
					it++;
				}
			}
		}
	} 
}

void CGame::updateQuadTree(sf::RenderWindow & App)
{
	collisionTree->clear();
	
	collisionTree->debugDraw(App);

	BOOST_FOREACH(CollisionObject *cobject, gResources.m_collisionObjects)
	{
		collisionTree->addObject(cobject);
		//cobject->draw(App);
	}

	
	
}

void CGame::manageGameStates(sf::RenderWindow & App)
{

	switch(gameState)
	{

	case CGame::LOADING :
		{
			gDDraw.add("Laduje poziom\n");


			break;
		}

	case CGame::IDLE :
		{
			gDDraw.add("IDLUJE\n");

			if(m_idle)
			{
				callScriptFunction("performIdleAction");
			}
			else
			{
				m_idle = true;
				callScriptFunction("startIdleAction");
			}


			// rysowanie statyczne
			App.setView(App.getDefaultView());
			drawGui(App);

			break;
		}

	case CGame::PLAYING :
		{
			gDDraw.add("GRAM\n");
			

			// rysowanie dynamiczne
			App.setView(*m_view);
			m_view->setCenter(m_player->getPosition());

			if(gResources.pTmxMap) gResources.drawMap(App);

			// aktualizuje drzewo kolizji
			updateQuadTree(App);


			// obsługa gracza
			m_player->update(App, m_deltaTime);
			m_player->draw(App);
			

			// rysowanie statyczne
			App.setView(App.getDefaultView());
			drawGui(App);



			break;
		}

	case CGame::PAUSE :
		{
			gDDraw.add("PAUSA\n");

			break;
		}


	} // end switch


}

void CGame::timeToLoadNewLevel(int level)
{
  gResources.loadLevel(level);
  m_player->setPosition( gResources.loadPlayerStartPosition() );
  gameState = PLAYING;
}