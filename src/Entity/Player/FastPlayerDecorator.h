#ifndef GAME_FASTPLAYERDECORATOR_H
#define GAME_FASTPLAYERDECORATOR_H

#include "PlayerDecorator.h"

class FastPlayerDecorator : public PlayerDecorator
{
public:
	explicit FastPlayerDecorator(const std::shared_ptr<IPlayer>& player);
	void update(float elapsedTime, Field &field, std::vector<std::shared_ptr<Bullet>> &bullets) override;
	void movePlayerToCenter() override;
	void restoreHealth() override;
	void setSpeed(float newSpeed) override;
	int getHealth() override;
	sf::Vector2f getPosition() override;
	Direction& getMoveDirection() override;
	float getMoveTimer() override;
	sf::RectangleShape getShape() const override;
	void setMoveTimer(float newTime) override;
	void setHealth(int newHealth) override;
	void setType(EntityType newType) override;
	void decrementHealth() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void setItem(std::shared_ptr<IItem> newItem) override;
	std::shared_ptr<IItem> getItem() override;
};


#endif //GAME_FASTPLAYERDECORATOR_H
