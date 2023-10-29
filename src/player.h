#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "field.h"
#include "direction.h"

extern const char PLAYER_TEXTURE[];

class Player : public sf::Drawable
{
 public:
	explicit Player(sf::Vector2f position);
	~Player() override = default;
	void update(float elapsedTime, Field& field);
	void handleKeyPress(const sf::Event::KeyEvent& event);
	void handleKeyRelease(const sf::Event::KeyEvent& event);
	sf::RectangleShape getShape();
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::RectangleShape shape;
	sf::Texture texture;
	Direction moveDirection = Direction::NONE;
	Direction attackDirection = Direction::NONE;
};

#endif //_PLAYER_H_