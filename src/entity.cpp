#include <iostream>
#include "entity.h"
#include "gameConstants.h"

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
{}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}