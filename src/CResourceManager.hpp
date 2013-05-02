#ifndef CRESNAGER_H
#define CRESNAGER_H

#include "headers.h"

#ifndef gResources
#define gResources CResourceManager::GetReference()
#endif

class CResourceManager: public TSingleton<CResourceManager>
{
private:
    void clearResources();

public:
	CResourceManager();

	// return const sf::Image
	const sf::Image & getImage(const std::string & filename);

    // add button
    void addButton(sf::Vector2f position, size_t charSize, sf::String text, std::string ActionToDo, std::string ID, bool hide, sf::Color normalColor = sf::Color::Red, sf::Color hoverColor = sf::Color::Green);

    // add textbox
    void addTextBox(sf::Vector2f position, size_t charSize, sf::String text, std::string ID, bool hide = true, sf::Color color = sf::Color::Red);

    // add timed text box
    void addTimedTextBox(sf::Vector2f position, size_t charSize, sf::String text, std::string ID, int milisec = 0, sf::Color color = sf::Color::Red);

	//	load images to memory via filename
	bool loadImage(const std::string & filename);

	// remove image from memory via filename
	void deleteImage(const std::string & filename);

	// return size of images container
	size_t getImgContainerSize();

	// lista ze wszystkimi elementami GUI
	std::list<class CGuiElement*> m_guiElements;

	// return current default font
	const sf::Font & getFont();

	// load and set font to use as default
	void setDefaultFont(const char *pathToFont = PATHTOFONT);

    //lvl = 0 - Menu glowne
    void loadLevel(int lvl);

    // return button or null
    class CGuiElement *findGUIElement(const char* id);

	// rysuje mape, komentarz zbędny
	void drawMap(sf::RenderWindow & App);

	// load map from *.tmx file (csv encoding)
	void loadTmxMap(const std::string &pathToMapFile);

	// na podstawie załadowanego Tmx tworzy mape i zapisuje do sprita
	void generateTextureMap();

	// tworzy mini-teksture o podanych wymiarach w gidach ( X,Y - od którego kafelka na mapie stworzyć teksture. SizeX,SizyY - ile kafelków ma się w niej zawierać )
	// i zwraca wskaźnik na sprite który ją zawiera
	sf::Sprite* createTextureByGID(unsigned int x, unsigned int y, unsigned int SizeX, unsigned int SizeY);

	// pointer to loaded map
	class TmxMap* pTmxMap;

	// z załadowanej mapy szuka objectgrup StartPosition i zwraca pozycję startową. 
	// jak nie znajdzie to zwraca (0,0)
	sf::Vector2f loadPlayerStartPosition();

	// wskaźnik na gotowego sprita z mapą
	sf::Sprite *mapSprite;

	// ładuje wszystkie elementy statyczne z którymi coś może kolidować (ściany, etc)
	// wszystkie elementy z grupy Collision w mapie TMX
	void loadStaticColliders();
	std::vector<CollisionObject*> m_collisionObjects;






	//////////////////////////////Thor Approved///////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	std::shared_ptr<sf::Image> getImagePointer(const std::string path);
	bool loadImageKey(const std::string path);

	//////////////////////////////////////////////////////////////////////////

private:
	std::map<std::string , sf::Image > m_images;
	thor::MultiResourceCache m_multiCache;


	// wskaźnik na domyślną czcionke
	sf::Font *m_font;

	// wskaźnik na teksture mapy
	sf::RenderTexture *rendtex;

	// zawiera wszystkie sprite'y składające się na całą mape
	std::list<sf::Sprite*> m_mapSprites;

};
#endif
