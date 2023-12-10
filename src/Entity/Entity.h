#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "SFML/Graphics.hpp"
#include "cstring"
#include "../Field/Field.h"
#include "memory"
#include "../Common/Direction.h"
#include "IEntity.h"
#include "EntityType.h"

class Entity : public IEntity
{
 public:
	Entity(
		const std::string& texturePath,
		sf::Vector2f position
		);
	float getSpeed();
	void setSpeed(float newSpeed) override;
	Direction& getMoveDirection() override;
	int getHealth() override;
	void setHealth(int newHealth) override;
	sf::Vector2f getPosition() override;
	sf::RectangleShape getShape() const override;
	EntityType getType() override;
	void setType(EntityType newType);
	float getMoveTimer() override;
	void setMoveTimer(float newTime) override;
	sf::Vector2f getMovement(float elapsedTime, Field& field);
	sf::RectangleShape shape;
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Texture texture;
 protected:
	float moveTimer = 0;
	EntityType type = EntityType::ENEMY;
	int health;
	float speed = 0;
	Direction moveDirection = Direction::NONE;
};

#endif //_ENTITY_H_
