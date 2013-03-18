#ifndef CBUTT_H
#define CBUTT_H

#include "headers.h"

class CButton : public CGuiElement
{
public:
	CButton();

	CButton(guiType typ, sf::Vector2f position, size_t charSize, sf::String text, std::string ActionToDo, std::string ID, bool hide = true, sf::Color normalColor = sf::Color::Red, sf::Color hoverColor = sf::Color::Green);

	virtual void draw(sf::RenderTarget & target);
	void update(sf::RenderWindow & App);

	sf::FloatRect getRect();

	sf::Text *getText();

	const bool isHidden();

	std::string *getID();
	const std::string *getAction();

	void setHide(bool trueORfalse);

	void setNormalColor(const sf::Color color);
	void setHoverColor(const sf::Color color);

    void setText(const char* text);
    void setAction(const char* text);
    void setPosition(sf::Vector2f position);

	const sf::Vector2f getPosition();


	// Czy przycisk został uznany za kliknięty
	const bool wasClicked();
	// Przywraca przycisk do stanu "Nie kliknięty"
	void resetState();

	~CButton();

protected:
	size_t m_charSize;
	sf::String m_buttonText;
	std::string m_actionToDo;

	sf::Text m_text;
	sf::FloatRect m_fRect;
	sf::Vector2f m_position;

	sf::Color m_normalColor, m_hoverColor;

	bool m_hidden, m_clicked;

	std::string m_id;
};
#endif
