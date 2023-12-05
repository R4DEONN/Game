#ifndef GAME_IENEMY_H
#define GAME_IENEMY_H

#include "../IEntity.h"
#include "../../Field/Field.h"

class IEnemy : public IEntity
{
public:
	virtual void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<IEnemy>>& enemies, sf::Vector2f playerPosition) = 0;
};

#endif //GAME_IENEMY_H
