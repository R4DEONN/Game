#include <cmath>
#include <iostream>
#include <functional>
#include "Enemy.h"
#include "gameConstants.h"

Enemy::Enemy(const std::string& texturePath, sf::Vector2f position)
	: Entity(texturePath, position)
{
	direction = Direction::UP;
	health = 1;
	type = EntityType::ENEMY;
	speed = 200.f;
}

void Enemy::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities)
{
	moveTimer += elapsedTime;
	const char maxImages = 2;
	const float frameDuration = 0.25;
	const char frameSize = GameConstants::BLOCK_SIZE;
	const int curPixel = (int(moveTimer / frameDuration) % maxImages) * frameSize;
	shape.setTextureRect(sf::IntRect(curPixel, 0, frameSize, frameSize));
	if (moveTimer > 2)
	{
		moveTimer = 0;
	}
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
	for (std::shared_ptr<Entity> entity : entities)
	{
		if (entity->getType() == EntityType::BULLET)
		{
			sf::FloatRect bulletBounds = entity->getShape().getGlobalBounds();
			if (enemyBounds.intersects(bulletBounds))
			{
				isAlive = false;
				entity->setIsAlive(false);
				return;
			}
		}
		else if (entity->getType() == EntityType::PLAYER)
		{
			sf::FloatRect playerBounds = entity->getShape().getGlobalBounds();
			if (enemyBounds.intersects(playerBounds))
			{
				entity->setIsAlive(false);
				return;
			}
		}
	}
}