//
// Created by admin on 26.11.2023.
//

#include "CoffeeItem.h"
#include "../../Common/GameConstants.h"

CoffeeItem::CoffeeItem(sf::Vector2f itemPosition)
: Item(itemPosition)
{
	type = ItemType::COFFEE;
	texture.loadFromFile("../res/Coffee.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}

void CoffeeItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

void CoffeeItem::use()
{
}
