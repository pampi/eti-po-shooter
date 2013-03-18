#ifndef CTMXMAP_H
#define CTMXMAP_H

#include "headers.h"

// @Potraktuj to jak struktury dla mapy wlasciwej
class TmxMapTileset
{
public:
	int firstGid;
	std::string name;
	int tileWidth;
	int tileHeight;
	std::string filename;
};

class TmxMapLayer
{
public:
	std::string name;
	int width;
	int height;
	int *data;

	~TmxMapLayer()
	{
		delete []data;
	}
};

class TmxMapObject
{
public:
	std::string name;
	int x;
	int y;
	int width;
	int height;
};

class TmxMapObjectGroup
{
public:
	std::string name;
	int width;
	int height;
	bool visable;

	std::list<class TmxMapObject*> objects;

	~TmxMapObjectGroup()
	{
		while( !objects.empty() )
		{
			this->objects.pop_front();
		}
	}
};
// @Juz tego tak nie traktuj


class TmxMap
{
public:
	TmxMap() {};

	int width;
	int height;
	int tileWidth;
	int tileHeight;

	std::list<class TmxMapTileset*> tilesets;
	std::list<class TmxMapLayer*> layers;
	std::list<class TmxMapObjectGroup*> objects;

	~TmxMap()
	{
		while( !tilesets.empty() )
			tilesets.pop_front();

		while( !layers.empty() )
			tilesets.pop_front();

		while( !objects.empty() )
			tilesets.pop_front();
	}
};

#endif