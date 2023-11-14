#ifndef _UTILS_H_
#define _UTILS_H_

#include "SFML/Graphics.hpp"
#include "../Common/GameConstants.h"

static sf::FloatRect moveRect(const sf::FloatRect& rect, const sf::Vector2f& offset)
{
	return { rect.left + offset.x, rect.top + offset.y, rect.width, rect.height };
}

static sf::Vector2f getCenterCoordinates()
{
	sf::Vector2f position(
		sf::VideoMode::getDesktopMode().width / 2,
		sf::VideoMode::getDesktopMode().height / 2
	);
	return position;
}

static sf::Vector2f getFieldPoint(const int x, const int y)
{
	return {
		x * BLOCK_SIZE + CENTER_OFFSET_X + BLOCK_SIZE / 2,
		y * BLOCK_SIZE + CENTER_OFFSET_Y + BLOCK_SIZE / 2
	};
}

#endif //_UTILS_H_
