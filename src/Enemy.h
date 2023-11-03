#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "entity.h"
#include "direction.h"

class Enemy : public Entity
{
 public:
	Enemy(const std::string& texturePath, sf::Vector2f position);
	void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities) override;
 private:
	Direction direction;
};

#endif //_ENEMY_H_
