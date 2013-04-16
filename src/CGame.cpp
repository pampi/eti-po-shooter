#include "headers.h"

#define TIME_TO_IDLE 5

extern const char *strKey[];

CGame::CGame()
{
	m_inited = false;
    m_idle = false;
    m_lastEventTime = time(NULL);
    gDDraw << "Dupa";
    gLogger << CLogger::LOG_INFO << "CGame konstruktor";
}

int CGame::Step(sf::RenderWindow & App)
{
	for(;;)
	{
		if(!m_inited)
		{
			m_Init();
		}
        App.setKeyRepeatEnabled(true);

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

                for(int i=0; i<sf::Keyboard::KeyCount; i++)
                {
                    if(CInputHandler::GetInstance()->isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
                    {
                        SLuaArgument *arg = new SLuaArgument(strKey[m_event.key.code]);
                        callScriptFunction("keyPressed", 1, arg);
                        delete arg;
                    }
                }
            }
		} // events loop

		// clear window
		App.clear();

		// JĄDRO GRY \|/

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



        if(gResources.pTmxMap) App.draw( *gResources.mapSprite );
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

void CGame::m_Init()
{
	m_inited = true;

    // Laduj menu
    gResources.loadLevel(0);

    m_player = new CPlayer("1", sf::Vector2f(200,200), CActor::STAYING, 100.f, "res/img/MC.png");
	

}

void CGame::drawGui(sf::RenderWindow & App)
{
    for( std::list<class CGuiElement*>::iterator it = gResources.getGuiList()->begin(); it != gResources.getGuiList()->end(); it++ )
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
