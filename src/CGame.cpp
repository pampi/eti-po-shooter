#include "headers.h"

#define TIME_TO_IDLE 5

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define M_PI 3.14159265358979323846f

extern const char *strKey[];

CGame::CGame()
{
	m_inited = false;
    m_idle = false;
    m_lastEventTime = time(NULL);
    gLogger << CLogger::LOG_INFO << "CGame constructor";
	m_view = new sf::View(sf::FloatRect(0,0,1280,720));

	gameState = SHOWINGMENU;
	collisionTree = NULL;

	currentLevel = 0;
	bulletCounter = 0;
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

			if( gameState == EXITING )
			{
				return -1;
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
            //gameState = CGame::IDLE;
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
    gResources.loadLevel(currentLevel);

	m_player = new CPlayer("1", gResources.loadPlayerStartPosition(), CActor::STAYING, 100.f, 0.f, 0.f, "res/img/dude.png");
    


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
					break;
                }
                

            case CGuiElement::GUI_TEXTBOX:
                {
                    CTextBox *textbox=static_cast<CTextBox *>(*it);
                    if( !textbox->isHidden() )
                    {
						if( *textbox->getID() == "gameTimer" )
						{
							std::ostringstream buff;
							buff<<"Timer: "<<(int)gameTimer.getElapsedTime().asSeconds();
							textbox->setText( buff.str().c_str() );
						}

						if( *textbox->getID() == "bulletCounter" )
						{
							std::ostringstream buff;
							buff<<"Used bullets: "<<bulletCounter;
							textbox->setText( buff.str().c_str() );
						}
                        textbox->draw(App);
                    }
					break;
                }
               
			case CGuiElement::GUI_STATIC_OVERLAY:
				{
					CGuiOverlay *gui_overlay=static_cast<CGuiOverlay *>(*it);
					if( !gui_overlay->isHidden() )
					{
						if( *gui_overlay->getID() == "skill1" )
						{
							
						}
						gui_overlay->draw(App);
					}
					break;
				}

            case CGuiElement::GUI_TIMED_TEXTBOX:
                {
                    CTimedTextBox *timedTextBox = static_cast<CTimedTextBox *>(*it);
                    timedTextBox->draw(App);
					break;
                }
                
			case CGuiElement::GUI_BAR:
				{
					CProgressBar *progressBar = static_cast<CProgressBar *>(*it);
					if( !progressBar->isHidden() )
					{
						if( *progressBar->getID() == "stamina" )
						{
							progressBar->setValue( m_player->getPercentStamina() );
						}

						if( *progressBar->getID() == "hp" )
						{
							progressBar->setValue( m_player->getPercentHP() );
						}

						progressBar->draw(App);
					}
					
					break;
				}

            default:
				{
					break;
				}

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
	
	//collisionTree->debugDraw(App);

	// dodaj ściany do kolizji
	BOOST_FOREACH(CollisionObject *cobject, gResources.m_staticObjects)
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
#pragma region IDLE COS TAM

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
#pragma endregion
		}

	case CGame::PLAYING :
		{
			gDDraw.add("GRAM\n");
			

			// rysowanie dynamiczne
			App.setView(*m_view);
			m_view->setCenter(m_player->getPosition());

			// rysuj mapę
			if(gResources.pTmxMap) gResources.drawMap(App);

			// aktualizuje drzewo kolizji
			updateQuadTree(App);

			// aktualiazuje pociski
			updateBullets(App);

			// obsługa gracza
			m_player->update(App, m_deltaTime);
			m_player->draw(App);
			
			// aktualizacja ekspolzji
			updateExplosion(App, m_deltaTime);

			// rysowanie statyczne
			App.setView(App.getDefaultView());
			drawGui(App);



			break;
		}

	case CGame::SHOWINGMENU :
		{
			gDDraw.add("MENU\n");
			

			m_view->setCenter(650,450);
			App.setView(*m_view);

			// rysuj mapę
			if(gResources.pTmxMap) gResources.drawMap(App);
			
			m_player->update(App, m_deltaTime);
			m_player->draw(App);

			// rysowanie statyczne
			App.setView(App.getDefaultView());
			drawGui(App);
			break;
		}

	case CGame::PAUSE :
		{
			gDDraw.add("PAUZA\n");

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

void CGame::updateBullets(sf::RenderWindow & App)
{
	for(std::list< std::shared_ptr<CBullet> >::iterator it = mg_bulletsList.begin(); it != mg_bulletsList.end(); )
	{
		// sprawdzanie kolizji pocisków ze ścianami
		std::vector<CollisionObject*> odp = gGame->collisionTree->getObjectsAt( (*it)->fRect.top,  (*it)->fRect.left );
		BOOST_FOREACH(CollisionObject* obj, odp)
		{
			obj->draw(App);
			if( checkCircleRectangleCollisiton( (*it)->cShape, obj->rShape ) )
			{
				(*it)->setToDelete();
				addExplosion( (*it)->m_sprite.getPosition() );
			}
		}

		if( (*it)->toDelete() )
		{
			it = mg_bulletsList.erase(it);
		}
		else
		{
			(*it)->update(App, m_deltaTime.asSeconds());
			it++;
		}
		
	}
}

bool CGame::checkCircleRectangleCollisiton(sf::CircleShape &cShape, sf::RectangleShape &rShape)
{
	sf::Vector2f recCenter;
	recCenter.x = rShape.getPosition().x + (rShape.getSize().x /2);
	recCenter.y = rShape.getPosition().y + (rShape.getSize().y /2);
	

	float unrotatedCircleX = cos( rShape.getRotation()*M_PI / 180 ) * (cShape.getPosition().x - recCenter.x) - 
		sin( rShape.getRotation()*M_PI / 180 ) * (cShape.getPosition().y - recCenter.y) + recCenter.x;

	float unrotatedCircleY  = sin( rShape.getRotation()*M_PI / 180 ) * (cShape.getPosition().x - recCenter.x) + 
		cos( rShape.getRotation()*M_PI / 180 ) * (cShape.getPosition().y - recCenter.y) + recCenter.y;

	// Closest point in the rectangle to the center of circle rotated backwards(unrotated)
	float closestX, closestY;

	// Find the unrotated closest x point from center of unrotated circle
	if (unrotatedCircleX  < rShape.getPosition().x )
		closestX = rShape.getPosition().x;
	else if (unrotatedCircleX  > rShape.getPosition().x + rShape.getSize().x)
		closestX = rShape.getPosition().x + rShape.getSize().x;
	else
		closestX = unrotatedCircleX ;

	// Find the unrotated closest y point from center of unrotated circle
	if (unrotatedCircleY < rShape.getPosition().y)
		closestY = rShape.getPosition().y;
	else if (unrotatedCircleY > rShape.getPosition().y + rShape.getSize().y)
		closestY = rShape.getPosition().y + rShape.getSize().y;
	else
		closestY = unrotatedCircleY;

	// Determine collision
	bool collision = false;

	float distance = findDistance(unrotatedCircleX , unrotatedCircleY, closestX, closestY);
	if (distance < cShape.getRadius() )
		collision = true; // Collision
	else
		collision = false;

	return collision;
}

float CGame::findDistance(float fromX, float fromY, float toX, float toY)
{
	float a = abs( fromX - toX );
	float b = abs( fromY - toY );

	return sqrt( (a*a) + (b*b) );
}