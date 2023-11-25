//
// Created by admin on 22.11.2023.
//

#ifndef GAME_IENTITY_H
#define GAME_IENTITY_H

#include "SFML/Graphics/RectangleShape.hpp"
#include "EntityType.h"

class IEntity : public sf::Drawable
{
public:
	virtual Direction& getMoveDirection() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual int getHealth() = 0;
	virtual void setHealth(int newHealth) = 0;
	virtual void setSpeed(float newSpeed) = 0;
	virtual void setType(EntityType newType) = 0;
	virtual float getMoveTimer() = 0;
	virtual void setMoveTimer(float newTime) = 0;
	virtual void decrementHealth() = 0;
	virtual sf::RectangleShape getShape() const = 0;
};

#endif //GAME_IENTITY_H
