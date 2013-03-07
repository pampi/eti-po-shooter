#ifndef CRESNAGER_H
#define CRESNAGER_H

#include "headers.h"
#include "CTextButton.h"
#include "CMenuTextButton.h"

class CResourceManager
{
private:
    void clearResources();

public:
	CResourceManager();

	// return const sf::Image
	const sf::Image & getImage(const std::string & filename);

	//	load images to memory via filename
	bool loadImage(const std::string & filename);

	// remove image from memory via filename
	void deleteImage(const std::string & filename);

	// return size of resource container
	int getMapSize();

	// return current default font
	const sf::Font & getFont();

	void setDefaultFont(const char *pathToFont = PATHTOFONT);

    //lvl = 0 - Menu glowne
    void loadLevel(int lvl);
	
private:
	std::map<std::string , sf::Image > m_images;

	sf::Font *m_font;


};
#endif
