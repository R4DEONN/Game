//
// Created by admin on 22.11.2023.
//

#include "Item.h"
#include "../Common/GameConstants.h"

Item::Item(sf::Vector2f itemPosition)
{
	position = itemPosition;
	shape.setPosition(position);
	shape.setOrigin({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}

void Item::use()
{

}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

sf::RectangleShape Item::getShape()
{
	return shape;
}
