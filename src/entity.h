#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include "cstring"
#include "field.h"

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
	virtual void update(float elapsedTime, Field& field, std::vector<Entity*>& vector);
	bool getIsAlive();
	float getSpeed();
	void setIsAlive(bool IsAlive);
	sf::RectangleShape getShape();
	EntityType getType();
	virtual void handleKeyPress(const sf::Event::KeyEvent& event);
	virtual void handleKeyRelease(const sf::Event::KeyEvent& event);
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Texture texture;
 protected:
	float moveTimer = 0;
	EntityType type;
	sf::RectangleShape shape;
	bool isAlive;
	int health;
	float speed = 0;
};

#endif //_ENTITY_H_
