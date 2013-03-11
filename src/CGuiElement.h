#ifndef CGUIELE_H
#define CGUIELE_H

#include "headers.h"

class CGuiElement
{
public:
	virtual void draw(sf::RenderTarget & target)=0;
	enum guiType { GUI_NOPE, GUI_BUTTON, GUI_BAR, GUI_CHYBA_KURWA_NIE };
	guiType type;
};
#endif