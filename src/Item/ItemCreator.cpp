//
// Created by admin on 26.11.2023.
//

#include "ItemCreator.h"
#include "items/CoffeeItem.h"

std::shared_ptr<IItem> ItemCreator::createItem(ItemType type, sf::Vector2f position)
{
	switch (type)
	{
	case ItemType::COFFEE:
		return std::make_shared<CoffeeItem>(position);
	}
	return std::make_shared<Item>(position);
}
