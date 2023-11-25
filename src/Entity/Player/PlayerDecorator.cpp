#include "PlayerDecorator.h"

#include <utility>

PlayerDecorator::PlayerDecorator(std::shared_ptr<IPlayer> player)
{
	this->player = std::move(player);
}

void PlayerDecorator::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets)
{
	player->update(elapsedTime, field, bullets);
}

void PlayerDecorator::movePlayerToCenter()
{
	player->movePlayerToCenter();
}

void PlayerDecorator::restoreHealth()
{
	player->restoreHealth();
}

void PlayerDecorator::setSpeed(float newSpeed)
{
	player->setSpeed(newSpeed);
}

int PlayerDecorator::getHealth()
{
	return player->getHealth();
}

sf::Vector2f PlayerDecorator::getPosition()
{
	return player->getPosition();
}

Direction& PlayerDecorator::getMoveDirection()
{
	return player->getMoveDirection();
}

float PlayerDecorator::getMoveTimer()
{
	return player->getMoveTimer();
}

sf::RectangleShape PlayerDecorator::getShape() const
{
	return player->getShape();
}

void PlayerDecorator::setMoveTimer(float newTime)
{
	player->setMoveTimer(newTime);
}

void PlayerDecorator::setHealth(int newHealth)
{
	player->setHealth(newHealth);
}

void PlayerDecorator::setType(EntityType newType)
{
	player->setType(newType);
}

void PlayerDecorator::decrementHealth()
{
	player->decrementHealth();
}

void PlayerDecorator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);
}