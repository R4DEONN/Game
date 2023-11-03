#ifndef _FIELD_H_
#define _FIELD_H_

#include <SFML/Graphics.hpp>
#include "cell.h"
#include <memory>

 class Field : public sf::Drawable
{
 public:
	Field();
	void draw(sf::RenderWindow &window);
	static sf::Vector2f getPlayerStartPosition();
	sf::Vector2f checkFieldWallsCollision(const sf::FloatRect &oldBounds, const sf::Vector2f &movement);
	void update(float elapsedTime);
 private:
	float moveTimer = 0;
	sf::Vector2f checkFieldGameCollision(const sf::FloatRect &oldBounds, const sf::Vector2f &movement);
	size_t width = 16;
	size_t height = 16;
	std::vector<std::shared_ptr<Cell>> cells;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //_FIELD_H_
