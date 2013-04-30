#include "headers.h"

CollisionObject::CollisionObject()
{

}

CollisionObject::CollisionObject(float _x, float _y, float _width, float _height, Type _typ) : 
	x ( _x ), 
	y ( _y ), 
	width ( _width ), 
	height ( _height ), 
	typ ( _typ)
{
	shape.setPosition( x, y );
	shape.setSize( sf::Vector2f( width, height ) );
	shape.setFillColor( sf::Color( 32, 128, 255 ) );
}

void CollisionObject::draw( sf::RenderTarget &canvas ) {
	canvas.draw( shape );
}




CQuadTree::CQuadTree()
{

}

CQuadTree::CQuadTree(float _x, float _y, float _width, float _height, int _level, int _maxLevel) :
	x		(_x),
	y		(_y),
	width	(_width),
	height	(_height),
	level	(_level),
	maxLevel(_maxLevel)
{
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(64, 128, 255));

	if (level == maxLevel) 
	{
		return;
	}

	NW = new CQuadTree(x, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
	NE = new CQuadTree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, maxLevel);
	SW = new CQuadTree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
	SE = new CQuadTree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, maxLevel);
	
}

CQuadTree::~CQuadTree()
{
	if (level == maxLevel)
		return;

	delete NW;
	delete NE;
	delete SW;
	delete SE;
}