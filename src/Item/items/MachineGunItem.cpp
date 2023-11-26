#include "MachineGunItem.h"
#include "../../Common/GameConstants.h"

MachineGunItem::MachineGunItem(sf::Vector2f itemPosition)
	: Item(itemPosition)
{
	type = ItemType::MACHINE_GUN;
	texture.loadFromFile("../res/machine_gun.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}