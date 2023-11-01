#include "cmath"
#include "bullet.h"

const float FORTY_FIVE_DEGREES_COEF = float(std::sqrt(2)) / 2;

Bullet::Bullet(const std::string& texturePath, sf::Vector2f position, Direction direction)
: Entity(texturePath, position)
{
	speed = 1000.f;
	switch (direction)
	{
	case Direction::UP:
		step = {0, -speed};
		break;
	case Direction::UP_LEFT:
		step = {-speed * FORTY_FIVE_DEGREES_COEF, -speed * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::UP_RIGHT:
		step = {+speed * FORTY_FIVE_DEGREES_COEF, -speed * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::DOWN:
		step = {0, +speed};
		break;
	case Direction::DOWN_LEFT:
		step = {-speed * FORTY_FIVE_DEGREES_COEF, +speed * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::DOWN_RIGHT:
		step = {+speed * FORTY_FIVE_DEGREES_COEF, +speed * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::LEFT:
		step = {-speed, 0};
		break;
	case Direction::RIGHT:
		step = {+speed, 0};
		break;
	case Direction::NONE:
		break;
	}
}

void Bullet::update(float elapsedTime, Field& field)
{
	const sf::Vector2f movement = step * elapsedTime;
	shape.move(movement);
}