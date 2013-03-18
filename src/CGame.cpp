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

            /*if( m_event.type == sf::Event::KeyPressed )
            {
				if( m_event.key.code == sf::Keyboard::Escape )
				{
					return -1; // wyjdz z gry(-1)
				}

			
            }*/
            if(CInputHandler::GetInstance()->isKeyPressed(CInputHandler::Escape))
            {
                return -1;  //wyjdz z kodem bledu
            }
		} // events loop

		App.clear();

		// J¥DRO GRY \|/

		drawGui(App);


		// J¥DRO GRY /|\

		// tak se mo¿esz tu wrzuciæ coœ co potrzebujesz zobaczyæ, albo ³aduj w loga
#if (DRAWDEBUG)
		gDDraw.add((int) gFPS.getFPS() ,"FPS: ");
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
	gResources.loadMap("res/level/0/map1a.tmx");
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

					// stop dealing
					btn->resetState();
					it = gButtonClicked.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
	} 
}
