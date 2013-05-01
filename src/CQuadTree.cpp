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

	rect.left = x;
	rect.top = y;
	rect.height = height;
	rect.width = width;

	switch (_typ)
	{
	case PLAYER :
			 {
				 shape.setFillColor( sf::Color( 255, 128, 255 ) );
				 break;
			 }
	case WALL :
			 {
				 shape.setFillColor( sf::Color( 32, 128, 255 ) );
				 break;
			 }
			
	}
	
}

void CollisionObject::draw( sf::RenderTarget &canvas ) 
{
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

void CQuadTree::addObject(CollisionObject *cobject)
{
	if (level == maxLevel)
	{
		objects.push_back(cobject);
		return;
	}


	if (contains(NW, cobject)) 
	{
		NW->addObject(cobject); 
		return;
	} 
	else if (contains(NE, cobject)) 
	{
		NE->addObject(cobject); 
		return;
	} 
	else if (contains(SW, cobject)) 
	{
		SW->addObject(cobject); 
		return;
	} 
	else if (contains(SE, cobject)) 
	{
		SE->addObject(cobject); 
		return;
	}

	if (contains(this, cobject))
	{
		objects.push_back(cobject);
	}
}

std::vector<CollisionObject*> CQuadTree::getObjectsAt(float _x, float _y) 
{
	if (level == maxLevel) 
	{
		return objects;
	}

	std::vector<CollisionObject*> returnObjects, childReturnObjects;
	if (!objects.empty() ) 
	{
		returnObjects = objects;
	}

	if (_x > x + width / 2.0f && _x < x + width) 
	{
		if (_y > y + height / 2.0f && _y < y + height) 
		{
			childReturnObjects = SE->getObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		} 
		else if (_y > y && _y <= y + height / 2.0f) 
		{
			childReturnObjects = NE->getObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		}
	} 
	else if (_x > x && _x <= x + width / 2.0f) 
	{
		if (_y > y + height / 2.0f && _y < y + height) 
		{
			childReturnObjects = SW->getObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		} 
		else if (_y > y && _y <= y + height / 2.0f) 
		{
			childReturnObjects = NW->getObjectsAt(_x, _y);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			return returnObjects;
		}
	}

	return returnObjects;
}

void CQuadTree::clear() 
{
	if (level == maxLevel) 
	{
		objects.clear();
		return;
	} 
	else 
	{
		NW->clear();
		NE->clear();
		SW->clear();
		SE->clear();
	}

	if (!objects.empty()) 
	{
		objects.clear();
	}
}

void CQuadTree::debugDraw(sf::RenderTarget &canvas) 
{
	canvas.draw(shape);
	if (level != maxLevel) 
	{
		NW->debugDraw(canvas);
		NE->debugDraw(canvas);
		SW->debugDraw(canvas);
		SE->debugDraw(canvas);
	}
}

bool CQuadTree::contains(CQuadTree *child, CollisionObject *object) 
{
	return	 !(object->x < child->x ||
		object->y < child->y ||
		object->x > child->x + child->width  ||
		object->y > child->y + child->height ||
		object->x + object->width < child->x ||
		object->y + object->height < child->y ||
		object->x + object->width > child->x + child->width ||
		object->y + object->height > child->y + child->height);
}