#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "SFML/Graphics.hpp"
#include "cstring"
#include "../Field/Field.h"
#include "memory"
#include "../Common/Direction.h"

enum class EntityType
{
	PLAYER,
	ENEMY,
	BULLET
};

class Entity : public sf::Drawable
{
 public:
	Entity(
		const std::string& texturePath,
		sf::Vector2f position
		);
	float getSpeed() const;
	int getHealth() const;
	void decrementHealth();
	sf::Vector2f getPosition();
	sf::RectangleShape getShape();
	EntityType getType();
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Texture texture;
 protected:
	float moveTimer = 0;
	EntityType type;
	sf::RectangleShape shape;
	int health;
	float speed = 0;
	Direction moveDirection = Direction::NONE;

	sf::Vector2f getMovement(float elapsedTime, Field& field);
};

#endif //_ENTITY_H_
