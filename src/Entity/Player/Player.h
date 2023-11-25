#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SFML/Graphics.hpp"
#include "../Entity.h"
#include "../../Field/Field.h"
#include "../../Common/Direction.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "../Bullet.h"
#include "IPlayer.h"

class Player : public IPlayer
{
 public:
	Player(const std::string& texturePath, const std::string& footTexturePath, sf::Vector2f position);
	void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets) override;
	void movePlayerToCenter() override;
	void restoreHealth() override;
	void setSpeed(float newSpeed) override;
	sf::RectangleShape getShape() const override;
	int getHealth() override;
	sf::Vector2f getPosition() override;
	Direction& getMoveDirection() override;
	float getMoveTimer() override;
	void setMoveTimer(float newTime) override;
	void setHealth(int newHealth) override;
	void setType(EntityType newType) override;
	void decrementHealth() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
	Entity entity;
	float secondsFromLastShot = 1;
	Direction attackDirection = Direction::NONE;
	sf::Sound shoot;
	sf::SoundBuffer shootBuffer;
	sf::Texture footTexture;
	sf::RectangleShape foot;
	bool isTripleShoot = false;
	bool isEightShoot = false;

	void move(sf::Vector2f movement);

	void updateDirection(
		Direction& direction,
		sf::Keyboard::Key UpKey,
		sf::Keyboard::Key LeftKey,
		sf::Keyboard::Key DownKey,
		sf::Keyboard::Key RightKey
	);
};

#endif //_PLAYER_H_