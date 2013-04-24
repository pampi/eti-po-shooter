/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2013 Jan Haller
// Few updates: Maj0r (24-04-2013)
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include "headers.h"


#include <Thor/Aurora/Tools/ForEach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cassert>




CBigSprite::CBigSprite(): sf::Drawable(), sf::Transformable(), mSize(0.f, 0.f), mSplitSprites(), mColor(sf::Color::White)
{

}

CBigSprite::CBigSprite(const CBigTexture& texture): sf::Drawable(), sf::Transformable(), mSize(), mSplitSprites(), mColor(sf::Color::White)
{
	setTexture(texture);
}

void CBigSprite::setTexture(const CBigTexture& texture)
{
	mSize = texture.fillSprites(mColor, mSplitSprites);
}

void CBigSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	AURORA_FOREACH(const CSprite& sprite, mSplitSprites)
	{
		if (sprite.toDraw)
		{
			target.draw(sprite.sprite, states);
		}
	}
}

void CBigSprite::setColor(const sf::Color& color)
{
	mColor = color;
	AURORA_FOREACH(CSprite& sprite, mSplitSprites)
		sprite.sprite.setColor(color);
}

void CBigSprite::calculateSprites(const sf::FloatRect &size)
{
	AURORA_FOREACH(CSprite& sprite, mSplitSprites)
	{
		if(sprite.rect.intersects(size) )
		{
			sprite.toDraw = true;
		}
		else
		{
			sprite.toDraw = false;
		}
	}
}

sf::Color CBigSprite::getColor() const
{
	return mColor;
}

sf::FloatRect CBigSprite::getLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, mSize.x, mSize.y);
}

sf::FloatRect CBigSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}
