#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
#include "../Common/Direction.h"

class Enemy : public Entity
{
 public:
	Enemy(const std::string& texturePath, sf::Vector2f position);
	void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities) override;
 private:
	void updateDirection(sf::Vector2f playerPosition);
	void handleEnemiesCollision(sf::Vector2f& movement, std::vector<std::shared_ptr<Entity>>& entities);
};

#endif //_ENEMY_H_