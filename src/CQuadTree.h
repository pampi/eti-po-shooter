#ifndef CQUADTREE_H
#define CQUADTREE_H

#include "headers.h"

class CollisionObject
{
public:
	enum Type { DELTA, WALL, BULLET, PLAYER, ENEMY, ENEMYBULLET };
	CollisionObject();
	CollisionObject(float x, float y, float width, float height, Type typ = DELTA);

	void draw(sf::RenderTarget &canvas);

	float x, y, width, height;
	Type typ;

	sf::RectangleShape rShape;
	sf::FloatRect fRect;
	sf::CircleShape cShape;
};

class CQuadTree
{
public:
	CQuadTree();
	CQuadTree(float x, float y, float width, float height, int pLevel, int maxLevel);

	~CQuadTree();

	void addObject(CollisionObject *cobject);
	std::vector<CollisionObject*> getObjectsAt(float x, float y);
	void clear();
	void debugDraw(sf::RenderTarget &canvas);


private:
	float x;
	float y;
	float width;
	float height;
	int level;
	int maxLevel;
	std::vector<CollisionObject*> objects;

	CQuadTree *parent;
	CQuadTree *NW;
	CQuadTree *NE;
	CQuadTree *SW;
	CQuadTree *SE;

	sf::RectangleShape shape;

	bool contains(CQuadTree *child, CollisionObject *object);
};
#endif