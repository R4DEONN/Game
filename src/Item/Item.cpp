//
// Created by admin on 22.11.2023.
//

#include "Item.h"
#include "../Common/GameConstants.h"

Item::Item(sf::Vector2f itemPosition)
{
	shape.setPosition(itemPosition);
	shape.setPosition(itemPosition);
	shape.setOrigin({
		BLOCK_SIZE / 2,
		BLOCK_SIZE / 2,
	});

	type = ItemType::NONE;
}

void Item::use()
{

}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

sf::RectangleShape Item::getImmutableShape() const
{
	return shape;
}

void Item::setPosition(sf::Vector2f newPosition)
{
	shape.setPosition(newPosition);
}

ItemType Item::getType() const
{
	return type;
}
