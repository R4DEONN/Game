#include "NukeItem.h"
#include "../../Common/GameConstants.h"

NukeItem::NukeItem(sf::Vector2f itemPosition) : Item(itemPosition)
{
	type = ItemType::NUKE;
	texture.loadFromFile("../res/nuke.png");
	shape.setTexture(&texture);
	shape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE,
	});
}
