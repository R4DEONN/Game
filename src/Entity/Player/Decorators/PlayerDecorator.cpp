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

void PlayerDecorator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);
}

void PlayerDecorator::setItem(std::shared_ptr<IItem> newItem)
{
	player->setItem(newItem);
}

std::shared_ptr<IItem> PlayerDecorator::getItem()
{
	return player->getItem();
}

void PlayerDecorator::setDelayToShot(float newDelay)
{
	player->setDelayToShot(newDelay);
}

EntityType PlayerDecorator::getType()
{
	return player->getType();
}

void PlayerDecorator::setShootingType(ShootingType type)
{
	player->setShootingType(type);
}

float PlayerDecorator::getDelayToShot()
{
	return player->getDelayToShot();
}

float PlayerDecorator::getSpeed()
{
	return player->getSpeed();
}
