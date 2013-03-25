#ifndef CBUTT_H
#define CBUTT_H

#include "headers.h"

class CButton : public CGuiElement
{
public:
    CButton(guiType typ, sf::Vector2f position, size_t charSize, sf::String text, std::string ActionToDo, std::string ID, bool hide = true, sf::Color normalColor = sf::Color::Red, sf::Color hoverColor = sf::Color::Green);

	virtual void draw(sf::RenderTarget & target);
	void update(sf::RenderWindow & App);

	sf::FloatRect getRect();

	sf::Text *getText();

	const std::string *getAction();

	void setHoverColor(const sf::Color color);

    void setText(const char* text);
    void setAction(const char* text);


	// Czy przycisk został uznany za kliknięty
	const bool wasClicked();
	// Przywraca przycisk do stanu "Nie kliknięty"
	void resetState();

    virtual ~CButton();

protected:
	size_t m_charSize;
	sf::String m_buttonText;
	std::string m_actionToDo;

    sf::Text m_text;

    sf::Color m_hoverColor;

    bool m_clicked;
};
#endif
