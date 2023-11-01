#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "entity.h"
#include "field.h"
#include "direction.h"

class Player : public Entity
{
 public:
	Player(const std::string& texturePath, sf::Vector2f position);
	void update(float elapsedTime, Field& field, std::vector<Entity*>& entities);
	void handleKeyPress(const sf::Event::KeyEvent& event);
	void handleKeyRelease(const sf::Event::KeyEvent& event);
 private:
	Direction moveDirection = Direction::NONE;
	Direction attackDirection = Direction::NONE;
};

#endif //_PLAYER_H_