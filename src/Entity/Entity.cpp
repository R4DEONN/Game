#include <iostream>
#include <cmath>
#include "Entity.h"
#include "../Common/GameConstants.h"

Entity::Entity(const std::string& texturePath, const sf::Vector2f position)
{
	if (!texture.loadFromFile(texturePath))
	{
		//TODO Нормальео обрабатывать ошибку
		std::wcerr << L"Не удалось загрузить изображение" << std::endl;
		exit(1);
	}

	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
	shape.setPosition(position);
	shape.setTexture(&texture);
	shape.setTextureRect(sf::IntRect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
	shape.setOrigin(
		BLOCK_SIZE / 2,
		BLOCK_SIZE / 2
	);

	health = 1;
}

float Entity::getSpeed() const
{
	return speed;
}

void Entity::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

int Entity::getHealth()
{
	return health;
}

void Entity::setHealth(int newHealth)
{
	health = newHealth;
}

sf::RectangleShape Entity::getShape() const
{
	return shape;
}

Direction& Entity::getMoveDirection()
{
	return moveDirection;
}

EntityType Entity::getType()
{
	return type;
}

void Entity::setType(EntityType newType)
{
	type = newType;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

sf::Vector2f Entity::getMovement(const float elapsedTime, Field& field)
{
	const float step = speed * elapsedTime;
	sf::Vector2f movement(0.f, 0.f);

	switch (moveDirection)
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

	const sf::FloatRect entityBounds = shape.getGlobalBounds();
	movement = field.checkFieldWallsCollision(entityBounds, movement);

	return movement;
}

sf::Vector2f Entity::getPosition()
{
	float x = shape.getPosition().x;
	float y = shape.getPosition().y;
	return {x, y};
}

float Entity::getMoveTimer()
{
	return moveTimer;
}

void Entity::setMoveTimer(float newTime)
{
	moveTimer = newTime;
}
