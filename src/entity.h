#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include "cstring"
#include "field.h"

class Entity : public sf::Drawable
{
 public:
	Entity(
		const std::string& texturePath,
		sf::Vector2f position
		);
	virtual void update(float elapsedTime, Field& field);
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Texture texture;
 protected:
	sf::RectangleShape shape;
	bool isAlive;
	int health;
	float speed = 0;
};

#endif //_ENTITY_H_
