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

	// return size of resource container
	int getMapSize();

	// return current default font
	const sf::Font & getFont();

	// load and set font to use as default
	void setDefaultFont(const char *pathToFont = PATHTOFONT);

    //lvl = 0 - Menu glowne
    void loadLevel(int lvl);

    // return button or null
    class CGuiElement *findGUIElement(const char* id);

	// zwraca wskaźnik na liste, tylko po co ?
	std::list<class CGuiElement*> *getGuiList();

	// load map from *.tmx file (csv encoding)
	void loadTmxMap(const std::string &pathToMapFile);

	// na podstawie załadowanego Tmx tworzy mape i zapisuje do sprita
	void generateTextureMap();

	// pointer to loaded map
	class TmxMap* pTmxMap;

	// wskaźnik na gotowego sprita z mapą
	sf::Sprite *mapSprite;
	
private:
	std::map<std::string , sf::Image > m_images;

	// lista ze wszystkimi elementami GUI
	std::list<class CGuiElement*> m_guiElements;

	// wskaźnik na domyślną czcionke
	sf::Font *m_font;


};
#endif
