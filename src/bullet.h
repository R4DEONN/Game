#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include "field.h"
#include "direction.h"
#include "entity.h"

class Bullet : public Entity
{
 public:
	Bullet(const std::string& texturePath, sf::Vector2f position, Direction direction);
	void update(float elapsedTime, Field& field, std::vector<Entity*>& vector) override;
 private:
	sf::Vector2f step;
};

#endif //_BULLET_H_
