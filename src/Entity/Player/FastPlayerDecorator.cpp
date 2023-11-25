//
// Created by admin on 22.11.2023.
//

#include "FastPlayerDecorator.h"
#include "../../Common/GameConstants.h"

FastPlayerDecorator::FastPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	this->player = player;
}

void FastPlayerDecorator::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets)
{
	player->setSpeed(BLOCK_SIZE * 6);
	player->update(elapsedTime, field, bullets);
}

void FastPlayerDecorator::movePlayerToCenter()
{
	player->movePlayerToCenter();
}

void FastPlayerDecorator::restoreHealth()
{
	player->restoreHealth();
}

void FastPlayerDecorator::setSpeed(float newSpeed)
{
	player->setSpeed(newSpeed);
}

int FastPlayerDecorator::getHealth()
{
	return player->getHealth();
}

sf::Vector2f FastPlayerDecorator::getPosition()
{
	return player->getPosition();
}

Direction& FastPlayerDecorator::getMoveDirection()
{
	return player->getMoveDirection();
}

float FastPlayerDecorator::getMoveTimer()
{
	return player->getMoveTimer();
}

sf::RectangleShape FastPlayerDecorator::getShape() const
{
	return player->getShape();
}

void FastPlayerDecorator::setMoveTimer(float newTime)
{
	player->setMoveTimer(newTime);
}

void FastPlayerDecorator::setHealth(int newHealth)
{
	player->setHealth(newHealth);
}

void FastPlayerDecorator::setType(EntityType newType)
{
	player->setType(newType);
}

void FastPlayerDecorator::decrementHealth()
{
	player->decrementHealth();
}

void FastPlayerDecorator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);
}
