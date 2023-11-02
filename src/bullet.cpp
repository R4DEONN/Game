#include "cmath"
#include "bullet.h"

const float FORTY_FIVE_DEGREES_COEF = float(std::sqrt(2)) / 2;

Bullet::Bullet(const std::string& texturePath, sf::Vector2f position, Direction direction)
: Entity(texturePath, position)
{
	speed = 500.f;
	shape.setSize({
		12,
		12
	});
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

void Bullet::update(float elapsedTime, Field& field, std::vector<Entity*>& vector)
{
	sf::Vector2f movement = step * elapsedTime;

	const sf::FloatRect bulletBound = shape.getGlobalBounds();
	const sf::Vector2f newMovement = field.checkFieldWallsCollision(bulletBound, movement);

	if (movement != newMovement)
	{
		isAlive = false;
	}
	else
	{
		shape.move(movement);
	}
}