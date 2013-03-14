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
		gDDraw.add((int) gButtonClicked.size() ,"Buttony: ");
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

    //powiaz funkcje silnika z interfejsem Lua
    RegisterEngineFunctions();

    // Laduj menu
    gResources.loadLevel(0);
}

void CGame::drawGui(sf::RenderWindow & App)
{
	for( std::list<class CGuiElement*>::iterator it = gResources.getGuiList()->begin(); it != gResources.getGuiList()->end(); it++ )
	{
		CButton *btn=static_cast<CButton *>(*it);
		if(btn->type == CGuiElement::GUI_BUTTON)
		{
			if( !btn->isHidden() )
			{
				btn->update(App);
				btn->draw(App);
			}
		}
	}

	manageButtons();
}

void CGame::RegisterEngineFunctions()
{
    //GUI

    //setButtonText(id, text)
    lua_register(machine, "setButtonText", API4Lua::setButtonText);
    //setButtonAction(id, action)
    lua_register(machine, "setButtonAction", API4Lua::setButtonAction);
    //setButtonHide(id, boolean true/false)
    lua_register(machine, "setButtonHide", API4Lua::setButtonHide);
    //setButtonPosition(id, double x, double y)
    lua_register(machine, "setButtonPosition", API4Lua::setButtonPosition);
    //setButtonColor(id, "N"/"H", r, g, b, a)
    lua_register(machine, "setButtonColor", API4Lua::setButtonColor);

    //audio


    //mix
    //addScript(path_to_script)
    lua_register(machine, "addScript", API4Lua::loadAdditionalScript);
    //changeLevel(lvl_id)
    lua_register(machine, "changeLevel", API4Lua::changeLevel);
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
