//
// Created by admin on 26.11.2023.
//

#include "ItemCreator.h"
#include "items/CoffeeItem.h"
#include "items/HpItem.h"

std::shared_ptr<IItem> ItemCreator::createItem(ItemType type, sf::Vector2f position)
{
	switch (type)
	{
	case ItemType::COFFEE:
		return std::make_shared<CoffeeItem>(position);
	case ItemType::EXTRA_HP:
		return std::make_shared<HpItem>(position);
	default:
		return std::make_shared<Item>(position);
	}
}
