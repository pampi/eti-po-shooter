#ifndef CGUIOVERLAY_H
#define CGUIOVERLAY_H

#include "headers.h"

class CGuiOverlay : public CGuiElement
{
public:
	virtual void draw(sf::RenderTarget & target);

	CGuiOverlay(sf::Vector2f position, std::string ID, int height, int width, bool hide = true, bool active = false, std::string imgPathNormal = "", std::string imgPathActive = "");


	int getWidth() const;
	int getHeight() const;

	bool isActive() const;
	void setActive(bool trueORfalse);

private:
	int m_width, m_height;
	std::string m_imgPathNormal, m_imgPathActive;
	std::shared_ptr<sf::Texture> m_textureP;
	sf::Sprite m_sprite;
	bool m_active;
};
#endif