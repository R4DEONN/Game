#include <cmath>
#include <iostream>
#include "Enemy.h"

Enemy::Enemy(const std::string& texturePath, sf::Vector2f position)
	: Entity(texturePath, position)
{
	direction = Direction::UP;
	health = 1;
	speed = 200.f;
}

void Enemy::update(float elapsedTime, Field& field, std::vector<Entity*>& entities)
{
	const float step = speed * elapsedTime;
	sf::Vector2f movement(0.f, 0.f);
	switch (direction)
	{
	case Direction::UP:
		movement.y -= step;
		break;
	case Direction::UP_LEFT:
		movement.x -= step * std::sqrt(2) / 2;
		movement.y -= step * std::sqrt(2) / 2;
		break;
	case Direction::UP_RIGHT:
		movement.x += step * std::sqrt(2) / 2;
		movement.y -= step * std::sqrt(2) / 2;
		break;
	case Direction::DOWN:
		movement.y += step;
		break;
	case Direction::DOWN_LEFT:
		movement.x -= step * std::sqrt(2) / 2;
		movement.y += step * std::sqrt(2) / 2;
		break;
	case Direction::DOWN_RIGHT:
		movement.x += step * std::sqrt(2) / 2;
		movement.y += step * std::sqrt(2) / 2;
		break;
	case Direction::LEFT:
		movement.x -= step;
		break;
	case Direction::RIGHT:
		movement.x += step;
		break;
	case Direction::NONE:
		break;
	}

	const sf::FloatRect enemyBounds = shape.getGlobalBounds();
	movement = field.checkFieldWallsCollision(enemyBounds, movement);
	//TODO Вынести move в Player
	shape.move(movement);
	for (Entity* entity : entities)
	{
		if (entity->getSpeed() > 400)
		{
			sf::FloatRect entityBounds = entity->getShape().getGlobalBounds();
			if (enemyBounds.intersects(entityBounds))
			{
				isAlive = false;
				entity->setIsAlive(false);
			}
		}
	}
}