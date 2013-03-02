#ifndef CSCREEN_H
#define CSCREEN_H

#include "headers.h"

class CScreen
{
public:
	virtual int Step(sf::RenderWindow & App)=0;
};
#endif