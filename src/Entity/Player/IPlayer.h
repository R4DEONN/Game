//
// Created by admin on 22.11.2023.
//

#ifndef GAME_IPLAYER_H
#define GAME_IPLAYER_H

#include "../../Field/Field.h"
#include "../Bullet.h"
#include "../IEntity.h"
#include "../../Item/Item.h"

class IPlayer : public IEntity
{
public:
	virtual void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets) = 0;
	virtual void movePlayerToCenter() = 0;
	virtual void restoreHealth() = 0;
	virtual void setItem(std::shared_ptr<IItem> newItem) = 0;
	virtual std::shared_ptr<IItem> getItem() = 0;
//	virtual void setSpeed(float newSpeed) = 0;
//	virtual sf::RectangleShape getShape() = 0;
//	virtual sf::
};

#endif //GAME_IPLAYER_H
