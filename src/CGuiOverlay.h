#ifndef CGUIOVERLAY_H
#define CGUIOVERLAY_H

#include "headers.h"

class CGuiOverlay : public CGuiElement
{
public:
	virtual void draw(sf::RenderTarget & target);

	CGuiOverlay(sf::Vector2f position, std::string ID, int height, int width, bool hide = true, std::string imgPath = "");


	int getWidth() const;
	int getHeight() const;

private:
	int m_width, m_height;
	std::string m_imgPath;
	std::shared_ptr<sf::Texture> m_textureP;
	sf::Sprite m_sprite;
};
#endif