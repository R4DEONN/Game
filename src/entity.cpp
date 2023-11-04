#include <iostream>
#include <cmath>
#include "entity.h"
#include "gameConstants.h"
#include "direction.h"

Entity::Entity(const std::string& texturePath, const sf::Vector2f position)
{
	if (!texture.loadFromFile(texturePath))
	{
		//TODO Нормальео обрабатывать ошибку
		std::wcerr << L"Не удалось загрузить изображение" << std::endl;
		exit(1);
	}

	shape.setSize({
		GameConstants::BLOCK_SIZE,
		GameConstants::BLOCK_SIZE,
	});
	shape.setPosition(position);
	shape.setTexture(&texture);
	shape.setTextureRect(sf::IntRect(0, 0, GameConstants::BLOCK_SIZE, GameConstants::BLOCK_SIZE));
	shape.setOrigin(
		GameConstants::BLOCK_SIZE / 2,
		GameConstants::BLOCK_SIZE / 2
	);

	isAlive = true;
	health = 1;
}

bool Entity::getIsAlive()
{
	return isAlive;
}

float Entity::getSpeed()
{
	return speed;
}

sf::RectangleShape Entity::getShape()
{
	return shape;
}

EntityType Entity::getType()
{
	return type;
}

void Entity::setIsAlive(bool IsAlive)
{
	isAlive = IsAlive;
}

void Entity::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities)
{
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

	const sf::FloatRect playerBounds = shape.getGlobalBounds();
	movement = field.checkFieldWallsCollision(playerBounds, movement);

	return movement;
}

sf::Vector2f Entity::getPosition()
{
	float x = shape.getPosition().x + GameConstants::BLOCK_SIZE / 2;
	float y = shape.getPosition().y + GameConstants::BLOCK_SIZE / 2;
	return sf::Vector2f(x, y);
}
