#include "headers.h"

#define TIME_TO_IDLE 5

extern const char *strKey[];

CGame::CGame()
{
	m_inited = false;
    m_idle = false;
    m_lastEventTime = time(NULL);
    gLogger << CLogger::LOG_INFO << "CGame konstruktor";
	m_view = new sf::View(sf::FloatRect(0,0,1280,720));
}

int CGame::Step(sf::RenderWindow & App)
{
	
	for(;;)
	{
		if(!m_inited)
		{
			m_Init(App);
		}
        //App.setKeyRepeatEnabled(true);

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

		// JĄDRO GRY \|/

		// tick timer
		m_deltaTime = m_deltaClock.restart();

		#pragma region IDLE
		//jeśli IDLE
        if(time(NULL)>m_lastEventTime+TIME_TO_IDLE)
        {
            if(m_idle)
            {
                callScriptFunction("performIdleAction");
            }
            else
            {
                m_idle = true;
                callScriptFunction("startIdleAction");
            }
        }
		#pragma endregion

		App.setView(*m_view);
		m_view->setCenter(m_player->getPosition());
		
        if(gResources.pTmxMap) gResources.drawMap(App);
		
		// sprawdza kolizje
		checkCollisions(App);
		
        drawGui(App);

		// JĄDRO GRY /|\


#if (DRAWDEBUG)
        gDDraw.add((int) gFPS.getFPS() ,"FPS: ");
        gDDraw.draw(App);
#endif

		// obsługa gracza
		m_player->update(App, m_deltaTime);
		m_player->draw(App);


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

    // Laduj menu
    gResources.loadLevel(0);

    m_player = new CPlayer("1", gResources.loadPlayerStartPosition(), CActor::STAYING, 100.f, 0.f, 0.f, "res/img/dude.png");

	// tu by trzeba było podawać rozmiary całej mapy a nie tylko ekranu // TO DO
	m_quadtree = new CQuadTree(0, 0, 2000, 1000, 0, 5);

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

void CGame::checkCollisions(sf::RenderWindow & App)
{
	m_quadtree->clear();
	sf::RectangleShape pshape;
	pshape.setSize(sf::Vector2f(30,30));
	pshape.setPosition(m_player->getPosition().x -15.0f,  m_player->getPosition().y -15.0f);
	pshape.setFillColor(sf::Color::Red);
	//App.draw(pshape);
	sf::FloatRect prect(m_player->getPosition().x -15.0f,  m_player->getPosition().y -15.0f, 30, 30);
	//m_quadtree->debugDraw(App);

	BOOST_FOREACH(CollisionObject *cobject, gResources.m_collisionObjects)
	{
		m_quadtree->addObject(cobject);
		//cobject->draw(App);
	}

	std::vector<CollisionObject*> odp = m_quadtree->getObjectsAt( m_player->getPosition().x  -15.0f,  m_player->getPosition().y -15.0f  );
	BOOST_FOREACH(CollisionObject* obj, odp)
	{
		//std::cout<<odp.size()<<'\n';
		if( prect.intersects(obj->rect) )
		{
			//std::cout << "KOLIZJA\n";
			App.draw(pshape);
			break;
		}
	}
	
}