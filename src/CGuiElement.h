#ifndef CGUIELE_H
#define CGUIELE_H

#include "headers.h"

class CGuiElement
{
public:
	virtual void draw(sf::RenderTarget & target)=0;
};
#endif