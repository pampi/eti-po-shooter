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
	int spacing;
	int margin;
	int imageWidth;
	int imageHeight;
	std::string filename;
	std::string trans;
};

class TmxMapLayer
{
public:
	std::string name;
	int width;
	int height;
	std::vector< std::vector< int > >data;

	// możesz ogarnąć czy destuktory dobrze działają
	~TmxMapLayer()
	{
		for(size_t i=0; i<data.size(); i++)
		{
			data[i].clear();
		}
		data.clear();
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

	// możesz ogarnąć czy destuktory dobrze działają
	~TmxMapObjectGroup()
	{
		while( !objects.empty() )
		{
            TmxMapObject *pMapObject = (*objects.begin());
            delete pMapObject;
			objects.pop_front();
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

	TmxMapTileset* findTileset(int gid)
	{
		TmxMapTileset *tileset = 0;
		std::list<TmxMapTileset*>::iterator it = tilesets.begin();

		do
		{
			it++;
		} while( it!=tilesets.end() && ((*it)->firstGid < gid) );

		if(it!=tilesets.begin()) it--;
		tileset = (*it);

		return tileset;
	}

	// możesz ogarnąć czy destuktory dobrze działają
	~TmxMap()
	{
        TmxMapTileset *pTileset;
        TmxMapLayer *pLayer;
        TmxMapObjectGroup *pObjectGroup;

		while( !tilesets.empty() )
        {
            pTileset = (*tilesets.begin());
            delete pTileset;
			tilesets.pop_front();
        }

		while( !layers.empty() )
        {
            pLayer = (*layers.begin());
            delete pLayer;
            layers.pop_front();
        }

		while( !objects.empty() )
        {
            pObjectGroup = (*objects.begin());
            delete pObjectGroup;
            objects.pop_front();
        }
	}
};

#endif
