#include <iostream>
#include "entity.h"
#include "gameConstants.h"

Entity::Entity(const std::string& texturePath, const sf::Vector2f position)
{
	if (!this->texture.loadFromFile(texturePath))
	{
		//TODO Нормальео обрабатывать ошибку
		std::wcerr << L"Не удалось загрузить изображение" << std::endl;
		exit(1);
	}

	this->shape.setSize({
		GameConstants::BLOCK_SIZE,
		GameConstants::BLOCK_SIZE,
	});
	this->shape.setPosition(position);

	this->shape.setOrigin(
		GameConstants::BLOCK_SIZE / 2,
		GameConstants::BLOCK_SIZE / 2
	);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape, states);
}

sf::RectangleShape Entity::getShape()
{
	return this->shape;
}