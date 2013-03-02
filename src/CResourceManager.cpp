#include "headers.h"

const sf::Image & CResourceManager::getImage(const std::string & filename)
{ 
	//	//	checking is image exist in memory
	for(std::map<std::string, sf::Image>::const_iterator it = m_images.begin(); it != m_images.end(); it++)
	{
		if(filename == it->first)
			return it->second;
	}

	//	//	if not found nothing, use default blank
	sf::Image _image;
	m_images[filename] = _image;
	return m_images[filename];
}

bool CResourceManager::loadImage(const std::string & filename)
{
	sf::Image _image;
	if( _image.loadFromFile(filename) )
	{
		m_images[filename] = _image;
		return true;
	}
	return false;
}

int CResourceManager::getMapSize()
{
	return (int)m_images.size();
}

void CResourceManager::deleteImage(const std::string & filename)
{
    //Karny kutas nr. 1 (nie ważny jeśli używasz C++11 zamiast C++98) -> http://www.cplusplus.com/reference/map/map/erase/
    //std::map<std::string, sf::Image>::const_iterator it = m_images.find(filename);
    std::map<std::string, sf::Image>::iterator it = m_images.find(filename);
	if( it != m_images.end() )
	{
		m_images.erase( it );
	}
}

const sf::Font & CResourceManager::getFont() 
{
	return *m_font;
}

void CResourceManager::setDefaultFont(const char* path)
{
	m_font->loadFromFile(path);
}

CResourceManager::CResourceManager() 
{
	m_font = new sf::Font();
	setDefaultFont();
}
