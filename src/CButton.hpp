#ifndef CBUTT_H
#define CBUTT_H

#include "headers.h"

class CButton : public CTextBox
{
public:
    CButton(guiType typ, sf::Vector2f position, size_t charSize, sf::String text, std::string ActionToDo, std::string ID, bool hide = true, sf::Color normalColor = sf::Color::Red, sf::Color hoverColor = sf::Color::Green);

	virtual void draw(sf::RenderTarget & target);
	void update(sf::RenderWindow & App);

	const std::string *getAction();

	void setHoverColor(const sf::Color color);

    void setAction(const char* text);


	// Czy przycisk został uznany za kliknięty
	const bool wasClicked();
	// Przywraca przycisk do stanu "Nie kliknięty"
	void resetState();

    virtual ~CButton();

protected:
    std::string m_actionToDo;

    sf::Color m_hoverColor;

    bool m_clicked;
};
#endif
