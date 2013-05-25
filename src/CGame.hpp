#ifndef CGAME_H
#define CGAME_H

#include "headers.h"

class CGame : public CScreen, public CScript, public CSoundManager
{
public:
	CGame();
	~CGame();

	virtual int Step(sf::RenderWindow & App);

	class CPlayer *getPlayer();

	enum State { NOT_SURE, LOADING, PAUSE, IDLE, PLAYING, SHOWINGMENU, ABANDON_ERROR };

	State gameState;

	// drzewko kolizji
	CQuadTree *collisionTree;

	void timeToLoadNewLevel(int level);

	// Lista wszystkich globalnych pocisków
	std::list< std::shared_ptr<class CBullet> > mg_bulletsList;

private:
	sf::Event m_event;

    time_t m_lastEventTime;
    bool m_idle;

	bool m_inited;
	void m_Init(sf::RenderWindow & App);

	void manageButtons();
	void drawGui(sf::RenderWindow & App);

	sf::Time m_deltaTime;
	sf::Clock m_deltaClock;

	class CPlayer *m_player;

	sf::View *m_view;
	
	void manageGameStates(sf::RenderWindow & App);

	// Aktualizuje drzewo kolizji. Musi być wołane przed jakim kolwiek sprawdzaniem kolizji
	void updateQuadTree(sf::RenderWindow & App);

	// Aktualizuje pociski
	void updateBullets(sf::RenderWindow & App);

	static bool checkCircleRectangleCollisiton(sf::CircleShape &cShape, sf::RectangleShape &rShape);

	static float findDistance(float fromX, float fromY, float toX, float toY);
};
#endif
