//
// Created by admin on 22.11.2023.
//

#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "IItem.h"
#include "ItemType.h"

class Item : public IItem
{
public:
	explicit Item(sf::Vector2f itemPosition);
	void use() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	sf::RectangleShape getShape() override;
protected:
	ItemType type;
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Vector2f position;
};


#endif //GAME_ITEM_H
