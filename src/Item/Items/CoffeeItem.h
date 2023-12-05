#ifndef GAME_COFFEEITEM_H
#define GAME_COFFEEITEM_H


#include "../IItem.h"
#include "../Item.h"

class CoffeeItem : public Item
{
public:
	explicit CoffeeItem(sf::Vector2f itemPosition);
};


#endif //GAME_COFFEEITEM_H
