#include <cmath>
#include <iostream>
#include <functional>
#include "Enemy.h"
#include "../Common/GameConstants.h"
#include "../Field/Field.h"
#include "../Utils/Utils.h"

Enemy::Enemy(const std::string& texturePath, sf::Vector2f position)
	: Entity(texturePath, position)
{
	health = 0;
	type = EntityType::ENEMY;
	speed = 120.f;
}

void Enemy::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities)
{
	moveTimer += elapsedTime;
	const char maxImages = 2;
	const float frameDuration = 0.25;
	const char frameSize = 48;
	const int curPixel = (int(moveTimer / frameDuration) % maxImages) * frameSize;
	shape.setTextureRect(sf::IntRect(curPixel, 0, frameSize, frameSize));
	if (moveTimer > maxImages * frameDuration)
	{
		moveTimer = 0;
	}

	updateDirection(entities[0]->getPosition());
	auto movement = getMovement(elapsedTime, field);
	handleEnemiesCollision(movement, entities);
	//TODO Вынести move в Player
	shape.move(movement);
	for (const auto& entity : entities)
	{
		const auto enemyBounds = shape.getGlobalBounds();
		if (entity->getType() == EntityType::BULLET)
		{
			sf::FloatRect bulletBounds = entity->getShape().getGlobalBounds();
			if (enemyBounds.intersects(bulletBounds))
			{
				decrementHealth();
				entity->decrementHealth();
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

void Enemy::handleEnemiesCollision(sf::Vector2f& movement, std::vector<std::shared_ptr<Entity>>& entities)
{
	const sf::FloatRect oldBounds = shape.getGlobalBounds();
	sf::FloatRect newBounds = moveRect(oldBounds, movement);
	for (const auto& entity : entities)
	{
		if (entity->getType() != EntityType::ENEMY
			|| entity->getPosition() == getPosition())
		{
			continue;
		}

		sf::FloatRect entityBound = entity->getShape().getGlobalBounds();
		if (newBounds.intersects(entityBound))
		{
			const auto delta = entity->getPosition() - getPosition();

			if (delta.y < 0
				&& std::abs(delta.y) >= std::abs(delta.x)
				&& movement.y < 0)
			{
				movement.y = entityBound.top + entityBound.height - oldBounds.top;
			}
			else if (delta.y > 0
					 && std::abs(delta.y) >= std::abs(delta.x)
					 && movement.y > 0)
			{
				movement.y = entityBound.top - oldBounds.height - oldBounds.top;
			}
			else if (delta.x < 0
					 && std::abs(delta.y) <= std::abs(delta.x)
					 && movement.x < 0)
			{
				movement.x = entityBound.left + entityBound.width - oldBounds.left;
			}
			else if (delta.x > 0
					 && std::abs(delta.y) <= std::abs(delta.x)
					 && movement.x > 0)
			{
				movement.x = entityBound.left - oldBounds.width - oldBounds.left;
			}

			newBounds = moveRect(oldBounds, movement);
		}
	}
}
