//
// Created by admin on 27.11.2023.
//

#include "ShotgunItem.h"
#include "../../Common/GameConstants.h"

ShotgunItem::ShotgunItem(sf::Vector2f itemPosition)
: Item(itemPosition)
{
	type = ItemType::SHOTGUN;
	texture.loadFromFile("../res/shotgun.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}
