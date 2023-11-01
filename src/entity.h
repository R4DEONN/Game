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
	void update(float elapsedTime, Field& field);
	sf::RectangleShape getShape();
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape shape;
	sf::Texture texture;
	bool isAlive;
	int health;
	float speed;
};

#endif //_ENTITY_H_
