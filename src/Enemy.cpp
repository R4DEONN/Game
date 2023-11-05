#include <cmath>
#include <iostream>
#include <functional>
#include "Enemy.h"
#include "gameConstants.h"

Enemy::Enemy(const std::string& texturePath, sf::Vector2f position)
	: Entity(texturePath, position)
{
	health = 1;
	type = EntityType::ENEMY;
	speed = 120.f;
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

	updateDirection(entities[0]->getPosition());
	auto movement = getMovement(elapsedTime, field);
	//TODO Вынести move в Player
	shape.move(movement);
	for (std::shared_ptr<Entity> entity : entities)
	{
		const sf::FloatRect enemyBounds = shape.getGlobalBounds();
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

void Enemy::updateDirection(sf::Vector2f playerPosition)
{
	sf::Vector2f enemyPosition = getPosition();
	float delta = std::abs(playerPosition.x - enemyPosition.x) - std::abs(playerPosition.y - enemyPosition.y);
	if (delta > 10)
	{
		if (playerPosition.x < enemyPosition.x)
		{
			moveDirection = Direction::LEFT;
		}
		else
		{
			moveDirection = Direction::RIGHT;
		}
	}
	else if (delta < -10)
	{
		if (playerPosition.y < enemyPosition.y)
		{
			moveDirection = Direction::UP;
		}
		else
		{
			moveDirection = Direction::DOWN;
		}
	}
	else
	{
		if (playerPosition.y < enemyPosition.y
			&& playerPosition.x < enemyPosition.x)
		{
			moveDirection = Direction::UP_LEFT;
		}
		else if (playerPosition.y < enemyPosition.y
				 && playerPosition.x > enemyPosition.x)
		{
			moveDirection = Direction::UP_RIGHT;
		}
		else if (playerPosition.y > enemyPosition.y
				 && playerPosition.x > enemyPosition.x)
		{
			moveDirection = Direction::DOWN_RIGHT;
		}
		else
		{
			moveDirection = Direction::DOWN_LEFT;
		}
	}
}
