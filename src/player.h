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
	void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities) override;
	void updateDirection(
		Direction& direction,
		sf::Keyboard::Key UpKey,
		sf::Keyboard::Key LeftKey,
		sf::Keyboard::Key DownKey,
		sf::Keyboard::Key RightKey
	);
 private:
	float secondsFromLastShot = 1;
	Direction attackDirection = Direction::NONE;
};

#endif //_PLAYER_H_