//
// Created by admin on 26.11.2023.
//

#ifndef GAME_ITEMCREATOR_H
#define GAME_ITEMCREATOR_H


#include <memory>
#include "IItem.h"
#include "ItemType.h"

class ItemCreator
{
public:
	static std::shared_ptr<IItem> createItem(ItemType type, sf::Vector2f position);
};


#endif //GAME_ITEMCREATOR_H
