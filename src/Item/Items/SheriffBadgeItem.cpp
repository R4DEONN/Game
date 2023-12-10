#include "SheriffBadgeItem.h"
#include "../../Common/GameConstants.h"

SheriffBadgeItem::SheriffBadgeItem(sf::Vector2f itemPosition) : Item(itemPosition)
{
	type = ItemType::SHERIFF_BADGE;
	texture.loadFromFile("../res/sheriff_badge.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}
