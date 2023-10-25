#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>

enum class Direction
{
	NONE,
	UP,
	UP_RIGHT,
	UP_LEFT,
	DOWN,
	DOWN_RIGHT,
	DOWN_LEFT,
	LEFT,
	RIGHT
};

extern const char PLAYER_TEXTURE[];

class Player
{
 public:
	Player();
	void update(float elapsedTime);
	void handleKeyPress(const sf::Event::KeyEvent& event);
	void handleKeyRelease(const sf::Event::KeyEvent& event);
	sf::RectangleShape getShape();
 private:
	sf::RectangleShape shape;
	sf::Texture texture;
	Direction moveDirection = Direction::NONE;
	Direction attackDirection = Direction::NONE;
};

#endif //_PLAYER_H_