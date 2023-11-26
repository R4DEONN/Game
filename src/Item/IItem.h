#ifndef GAME_IITEM_H
#define GAME_IITEM_H

#include <SFML/Graphics.hpp>

class IItem : public sf::Drawable
{
public:
	virtual void use() = 0;
	virtual sf::RectangleShape getShape() = 0;
};

#endif //GAME_IITEM_H
