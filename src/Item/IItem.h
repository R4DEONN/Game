#ifndef GAME_IITEM_H
#define GAME_IITEM_H

#include <SFML/Graphics.hpp>
#include "ItemType.h"

class IItem : public sf::Drawable
{
public:
	virtual void use() = 0;
	virtual sf::RectangleShape getImmutableShape() const = 0;
	virtual ItemType getType() const = 0;
	virtual void setPosition(sf::Vector2f newPosition) = 0;
};

#endif //GAME_IITEM_H
