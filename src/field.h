#ifndef _FIELD_H_
#define _FIELD_H_

#include <SFML/Graphics.hpp>
#include "cell.h"

class Field
{
 public:
	Field();
	void draw(sf::RenderWindow &window);
	static sf::Vector2f getPlayerStartPosition();
	sf::Vector2f checkFieldWallsCollision(const sf::FloatRect &oldBounds, const sf::Vector2f &movement);
 private:
	sf::Vector2f checkFieldGameCollision(const sf::FloatRect &oldBounds, const sf::Vector2f &movement);
	size_t width = 16;
	size_t height = 16;
	std::vector<Cell> cells;
};

#endif //_FIELD_H_
