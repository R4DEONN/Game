#include "cmath"
#include "bullet.h"

constexpr const float BULLET_SPEED = 1000.f;
const float FORTY_FIVE_DEGREES_COEF = float(std::sqrt(2)) / 2;

Bullet::Bullet(sf::Vector2f position, Direction direction)
{
	this->position = position;
	switch (direction)
	{
	case Direction::UP:
		this->direction = {0, -BULLET_SPEED};
		break;
	case Direction::UP_LEFT:
		this->direction = {-BULLET_SPEED * FORTY_FIVE_DEGREES_COEF, -BULLET_SPEED * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::UP_RIGHT:
		this->direction = {+BULLET_SPEED * FORTY_FIVE_DEGREES_COEF, -BULLET_SPEED * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::DOWN:
		this->direction = {0, +BULLET_SPEED};
		break;
	case Direction::DOWN_LEFT:
		this->direction = {-BULLET_SPEED * FORTY_FIVE_DEGREES_COEF, +BULLET_SPEED * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::DOWN_RIGHT:
		this->direction = {+BULLET_SPEED * FORTY_FIVE_DEGREES_COEF, +BULLET_SPEED * FORTY_FIVE_DEGREES_COEF};
		break;
	case Direction::LEFT:
		this->direction = {-BULLET_SPEED, 0};
		break;
	case Direction::RIGHT:
		this->direction = {+BULLET_SPEED, 0};
		break;
	case Direction::NONE:
		break;
	}
}

void Bullet::update(float elapsedTime, Field& field)
{
	const float step = BULLET_SPEED * elapsedTime;
}