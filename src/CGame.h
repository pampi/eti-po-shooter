#ifndef CGAME_H
#define CGAME_H

#include "headers.h"

class CGame : public CScreen, public CScript, public CSoundManager, public CExplosionManager
{
public:
	CGame();
	~CGame();

	virtual int Step(sf::RenderWindow & App);

	class CPlayer *getPlayer();

	enum State { NOT_SURE, LOADING, PAUSE, IDLE, PLAYING, SHOWINGMENU, GAME_OVER, ABANDON_ERROR, EXITING };

	State gameState;

	// drzewko kolizji
	CQuadTree *collisionTree;

	void timeToLoadNewLevel(int level);

	static bool checkCircleRectangleCollisiton(sf::CircleShape &cShape, sf::RectangleShape &rShape);

	static float findDistance(float fromX, float fromY, float toX, float toY);

	static float findDistance(sf::Vector2f From, sf::Vector2f To);

	// Globalna lista wszystkich pocisków
	std::list< std::shared_ptr<class CBullet> > mg_bulletsList;

	// aktualny poziom na którym gramy
	int currentLevel;

	// ilość wystrzelonych pocisków
	int bulletCounter;

	// ilość zabitych zombi
	int corpseCounter;

	// czas aktualnego poziomu
	sf::Clock gameTimer;

	// Globalna lista wszystkich wrogów na mapie
	std::list< std::shared_ptr<class CEnemy> > mg_enemiesList;

private:
	sf::Event m_event;

    time_t m_lastEventTime;
    bool m_idle;

	bool m_inited;
	void m_Init(sf::RenderWindow & App);

	void manageButtons();
	void drawGui(sf::RenderWindow & App);

	sf::Time m_deltaTime;
	sf::Clock m_deltaClock, m_biteClock;

	class CPlayer *m_player;

	sf::View *m_view;

	sf::RectangleShape m_blackGround;

	// zarządza stanami gry
	void manageGameStates(sf::RenderWindow & App);

	// Aktualizuje drzewo kolizji. Musi być wołane przed jakim kolwiek sprawdzaniem kolizji
	void updateQuadTree(sf::RenderWindow & App);

	// Aktualizuje pociski
	void updateBullets(sf::RenderWindow & App);

	// Aktualizuje wrogów
	void updateEnemies(sf::RenderWindow & App);

	bool m_podsumowane;
	void gameOver(sf::RenderWindow & App);





#define SCORE_URL "http://eti-inquisition.cba.pl/add_score.php?"

	static char* getPCUsername()
	{
		char *username=new char[64];
		DWORD len=64;
		GetUserNameA(username, &len);
		username[len]=0;
		return username;
	}

	static void add_score_to_internet(unsigned int score, unsigned int bullets, const char* player_name=getPCUsername())
	{
		HINTERNET handle = InternetOpenA(0, INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
		if ( handle == 0 )
		{
			const DWORD error = ::GetLastError();
			printf("Jakis error!\n");
			return;
		}

		char completeURL[512];
		sprintf(completeURL, "%ss=%u&p=%s&b=%u", SCORE_URL, score, player_name, bullets);
		HINTERNET handle2=InternetOpenUrlA(handle, completeURL, 0, 0, INTERNET_FLAG_RELOAD, 0);

		Sleep(1000);
		InternetCloseHandle(handle2);
		InternetCloseHandle(handle);
	}


};
#endif
