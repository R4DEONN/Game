//
// Created by admin on 26.11.2023.
//

#ifndef GAME_COFFEEITEM_H
#define GAME_COFFEEITEM_H


#include "../IItem.h"
#include "../Item.h"

class CoffeeItem : public Item
{
public:
	explicit CoffeeItem(sf::Vector2f itemPosition);
	void use() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void setPosition(sf::Vector2f newPosition) override;
};


#endif //GAME_COFFEEITEM_H
