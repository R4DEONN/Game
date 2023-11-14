#ifndef _BULLET_H_
#define _BULLET_H_

#include "SFML/Graphics.hpp"
#include "../Field/Field.h"
#include "../Common/Direction.h"
#include "Entity.h"

class Bullet : public Entity
{
 public:
	Bullet(const std::string& texturePath, sf::Vector2f position, Direction direction);
	void update(float elapsedTime, Field& field);
 private:
	sf::Vector2f step;
};

#endif //_BULLET_H_
