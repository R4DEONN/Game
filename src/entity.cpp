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

void Entity::update(float elapsedTime, Field& field)
{}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}