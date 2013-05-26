#ifndef CPROGRESSBAR_H
#define CPROGRESSBAR_H

#include "headers.h"


class CProgressBar : public CGuiElement
{
public:
	virtual void draw(sf::RenderTarget & target);

	CProgressBar(sf::Vector2f position, std::string ID, int height, int width, float startValue = 50, bool hide = true, std::string imgPath = "", sf::Color barColor = sf::Color::Blue);

	int getWidth() const;
	int getHeight() const;

	void setValue(float value);
	float getValue() const;


private:
	int m_width, m_height;
	float m_value;
	std::string m_imgPath;
	std::shared_ptr<sf::Texture> m_textureP;
	sf::RectangleShape m_rShape;
	sf::Sprite m_sprite;

};
#endif