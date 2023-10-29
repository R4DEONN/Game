#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>
#include "field.h"
#include "direction.h"

class Bullet //: public sf::Drawable
{
 public:
	Bullet(sf::Vector2f position, Direction direction);
	//~Bullet() override = default;
	void update(float elapsedTime, Field& field);
//	sf::RectangleShape getShape();
 private:
//	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f direction;
};

#endif //_BULLET_H_
