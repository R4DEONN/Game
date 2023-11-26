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
	sf::RectangleShape getImmutableShape() const override;
	void setPosition(sf::Vector2f newPosition) override;
	ItemType getType() const override;
protected:
	ItemType type;
	sf::RectangleShape shape;
	sf::Texture texture;
};


#endif //GAME_ITEM_H
