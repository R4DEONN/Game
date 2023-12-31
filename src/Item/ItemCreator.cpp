#include "ItemCreator.h"
#include "items/CoffeeItem.h"
#include "items/HpItem.h"
#include "items/MachineGunItem.h"
#include "items/ShotgunItem.h"
#include "Items/WagonWheelItem.h"
#include "Items/NukeItem.h"
#include "Items/SheriffBadgeItem.h"

std::shared_ptr<IItem> ItemCreator::createItem(ItemType type, sf::Vector2f position)
{
	switch (type)
	{
	case ItemType::COFFEE:
		return std::make_shared<CoffeeItem>(position);
	case ItemType::EXTRA_HP:
		return std::make_shared<HpItem>(position);
	case ItemType::MACHINE_GUN:
		return std::make_shared<MachineGunItem>(position);
	case ItemType::SHOTGUN:
		return std::make_shared<ShotgunItem>(position);
	case ItemType::WAGON_WHEEL:
		return std::make_shared<WagonWheelItem>(position);
	case ItemType::NUKE:
		return std::make_shared<NukeItem>(position);
	case ItemType::SHERIFF_BADGE:
		return std::make_shared<SheriffBadgeItem>(position);
	default:
		return std::make_shared<Item>(position);
	}
}
