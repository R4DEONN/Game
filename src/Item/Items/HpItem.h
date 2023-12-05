//
// Created by admin on 26.11.2023.
//

#ifndef GAME_HPITEM_H
#define GAME_HPITEM_H


#include "../Item.h"

class HpItem : public Item
{
public:
	explicit HpItem(sf::Vector2f itemPosition);
};


#endif //GAME_HPITEM_H
