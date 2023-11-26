#include "HpItem.h"
#include "../../Common/GameConstants.h"

HpItem::HpItem(sf::Vector2f itemPosition) : Item(itemPosition)
{
	type = ItemType::EXTRA_HP;
	texture.loadFromFile("../res/head.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}