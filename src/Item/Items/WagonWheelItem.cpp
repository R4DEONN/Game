#include "WagonWheelItem.h"
#include "../../Common/GameConstants.h"

WagonWheelItem::WagonWheelItem(sf::Vector2f itemPosition) : Item(itemPosition)
{
	type = ItemType::WAGON_WHEEL;
	texture.loadFromFile("../res/wagon_wheel.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}
