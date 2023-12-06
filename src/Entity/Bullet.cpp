#include "cmath"
#include "Bullet.h"
#include "../Common/GameConstants.h"

const float FORTY_FIVE_DEGREES_COEF = float(std::sqrt(2)) / 2;
const constexpr float THIRTY_DEGREES_COEF = 1.f / 2;
const float SIXTY_DEGREES_COEF = float(std::sqrt(3)) / 2;

Bullet::Bullet(const std::string& texturePath, sf::Vector2f position, Direction direction)
: Entity(texturePath, position)
{
	health = 0;
	shape.setTextureRect(sf::IntRect(0, 0, 12, 12));
	type = EntityType::BULLET;
	speed = BLOCK_SIZE * 8;
	shape.setSize({
		BLOCK_SIZE / 4,
		BLOCK_SIZE / 4,
	});
	switch (direction)
	{
	case Direction::UP:
		step = {0, -speed};
		break;
	case Direction::UP_RIGHT_THIRTY:
		step = {+speed * THIRTY_DEGREES_COEF, -speed * SIXTY_DEGREES_COEF};
		break;
	case Direction::UP_RIGHT_SIXTY:
		step = {+speed * SIXTY_DEGREES_COEF, -speed * THIRTY_DEGREES_COEF};
		break;
	case Direction::DOWN_RIGHT_THIRTY:
		step = {+speed * THIRTY_DEGREES_COEF, +speed * SIXTY_DEGREES_COEF};
		break;
	case Direction::DOWN_RIGHT_SIXTY:
		step = {+speed * SIXTY_DEGREES_COEF, +speed * THIRTY_DEGREES_COEF};
		break;
	case Direction::UP_LEFT_THIRTY:
		step = {-speed * THIRTY_DEGREES_COEF, -speed * SIXTY_DEGREES_COEF};
		break;
	case Direction::UP_LEFT_SIXTY:
		step = {-speed * SIXTY_DEGREES_COEF, -speed * THIRTY_DEGREES_COEF};
		break;
	case Direction::DOWN_LEFT_THIRTY:
		step = {-speed * THIRTY_DEGREES_COEF, +speed * SIXTY_DEGREES_COEF};
		break;
	case Direction::DOWN_LEFT_SIXTY:
		step = {-speed * SIXTY_DEGREES_COEF, +speed * THIRTY_DEGREES_COEF};
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
	sf::Vector2f movement = step * elapsedTime;

	const sf::FloatRect bulletBound = shape.getGlobalBounds();
	const sf::Vector2f newMovement = field.checkFieldWallsCollision(bulletBound, movement);

	if (movement != newMovement)
	{
        setHealth(getHealth() - 1);
	}
	else
	{
		shape.move(movement);
	}
}