//
// Created by admin on 22.11.2023.
//

#ifndef GAME_PLAYERDECORATOR_H
#define GAME_PLAYERDECORATOR_H

#include "IPlayer.h"

class PlayerDecorator : public IPlayer
{
public:
	explicit PlayerDecorator(std::shared_ptr<IPlayer> player);
	void update(float elapsedTime, Field &field, std::vector<std::shared_ptr<Bullet>> &bullets) override;
	void movePlayerToCenter() override;
	void restoreHealth() override;
	void setSpeed(float newSpeed) override;
	int getHealth() override;
	sf::Vector2f getPosition() override;
	Direction& getMoveDirection() override;
	float getMoveTimer() override;
	sf::RectangleShape getShape() const override;
	void setItem(std::shared_ptr<IItem> newItem) override;
	std::shared_ptr<IItem> getItem() override;
	void setMoveTimer(float newTime) override;
	void setHealth(int newHealth) override;
	void setType(EntityType newType) override;
	void decrementHealth() override;
	void setDelayToShot(float newDelay) override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	void shoot(std::vector<std::shared_ptr<Bullet>> &bullets, Direction direction) override;
	void setTripleShoot(bool isTripleShoot) override;
	void setEightShoot(bool isEightShoot) override;
protected:
	std::shared_ptr<IPlayer> player;
};


#endif //GAME_PLAYERDECORATOR_H
