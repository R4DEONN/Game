#include <cmath>
#include <iostream>
#include <functional>
#include "Enemy.h"
#include "../../Common/GameConstants.h"
#include "../../Field/Field.h"
#include "../../Utils/Utils.h"
#include "../Player/Player.h"

Enemy::Enemy(const std::string& texturePath, sf::Vector2f position)
	: entity(texturePath, position)
{
	entity.setType(EntityType::ENEMY);
	entity.setSpeed(BLOCK_SIZE * 2.5);
	entity.setHealth(0);
}

void Enemy::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<IEnemy>>& enemies, sf::Vector2f playerPosition)
{
	entity.setMoveTimer(entity.getMoveTimer() + elapsedTime);
	const char maxImages = 2;
	const float frameDuration = 0.25;
	const char frameSize = 48;
	const int curPixel = (int(entity.getMoveTimer() / frameDuration) % maxImages) * frameSize;
	entity.shape.setTextureRect(sf::IntRect(curPixel, 0, frameSize, frameSize));
	if (entity.getMoveTimer() > maxImages * frameDuration)
	{
		entity.setMoveTimer(0);
	}

	updateDirection(entity.getMoveDirection(), playerPosition);
	auto movement = entity.getMovement(elapsedTime, field);
	handleEnemiesCollision(movement, enemies);
	entity.shape.move(movement);

	for (const auto& enemy : enemies)
	{
		const auto enemyBounds = entity.getShape().getGlobalBounds();
		if (enemy->getType() == EntityType::BULLET)
		{
			sf::FloatRect bulletBounds = enemy->getShape().getGlobalBounds();
			if (enemyBounds.intersects(bulletBounds))
			{
				setHealth(getHealth() - 1);
				enemy->setHealth(enemy->getHealth() - 1);
				return;
			}
		}
	}
}

void Enemy::updateDirection(Direction& moveDirection, sf::Vector2f playerPosition)
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

void Enemy::handleEnemiesCollision(sf::Vector2f& movement, std::vector<std::shared_ptr<IEnemy>>& enemies)
{
	const sf::FloatRect oldBounds = entity.getShape().getGlobalBounds();
	sf::FloatRect newBounds = moveRect(oldBounds, movement);
	for (const auto& enemy : enemies)
	{
		if (enemy->getPosition() == getPosition())
		{
			continue;
		}

		sf::FloatRect entityBound = enemy->getShape().getGlobalBounds();
		if (newBounds.intersects(entityBound))
		{
			const auto delta = enemy->getPosition() - getPosition();

			const bool topCollision = delta.y < 0
								 && std::abs(delta.y) >= std::abs(delta.x)
								 && movement.y < 0;

			const bool bottomCollision = delta.y > 0
										&& std::abs(delta.y) >= std::abs(delta.x)
										&& movement.y > 0;

			const bool leftCollision = delta.x < 0
									   && std::abs(delta.y) <= std::abs(delta.x)
									   && movement.x < 0;

			const bool rightCollision = delta.x > 0
										&& std::abs(delta.y) <= std::abs(delta.x)
										&& movement.x > 0;

			if (topCollision)
			{
				movement.y = entityBound.top + entityBound.height - oldBounds.top;
			}
			else if (bottomCollision)
			{
				movement.y = entityBound.top - oldBounds.height - oldBounds.top;
			}
			else if (leftCollision)
			{
				movement.x = entityBound.left + entityBound.width - oldBounds.left;
			}
			else if (rightCollision)
			{
				movement.x = entityBound.left - oldBounds.width - oldBounds.left;
			}

			newBounds = moveRect(oldBounds, movement);
		}
	}
}

EntityType Enemy::getType()
{
	return entity.getType();
}

sf::RectangleShape Enemy::getShape() const
{
	return entity.getShape();
}

int Enemy::getHealth()
{
	return entity.getHealth();
}

sf::Vector2f Enemy::getPosition()
{
	return entity.getPosition();
}

Direction& Enemy::getMoveDirection()
{
	return entity.getMoveDirection();
}

float Enemy::getMoveTimer()
{
	return entity.getMoveTimer();
}

void Enemy::setSpeed(float newSpeed)
{
	entity.setSpeed(newSpeed);
}

void Enemy::setHealth(int newHealth)
{
	entity.setHealth(newHealth);
}

void Enemy::setMoveTimer(float newTime)
{
	entity.setMoveTimer(newTime);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(entity.getShape(), states);
}

float Enemy::getSpeed()
{
	return entity.getSpeed();
}
