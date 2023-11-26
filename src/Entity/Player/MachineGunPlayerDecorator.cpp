#include "MachineGunPlayerDecorator.h"
#include "../../Common/GameConstants.h"

MachineGunPlayerDecorator::MachineGunPlayerDecorator(const std::shared_ptr<IPlayer>& player)
	: PlayerDecorator(player)
{
	this->player = player;
	this->player->setDelayToShot(0.15);
}

void MachineGunPlayerDecorator::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets)
{
	player->update(elapsedTime, field, bullets);
}

void MachineGunPlayerDecorator::movePlayerToCenter()
{
	player->movePlayerToCenter();
}

void MachineGunPlayerDecorator::restoreHealth()
{
	player->restoreHealth();
}

void MachineGunPlayerDecorator::setSpeed(float newSpeed)
{
	player->setSpeed(newSpeed);
}

int MachineGunPlayerDecorator::getHealth()
{
	return player->getHealth();
}

sf::Vector2f MachineGunPlayerDecorator::getPosition()
{
	return player->getPosition();
}

Direction& MachineGunPlayerDecorator::getMoveDirection()
{
	return player->getMoveDirection();
}

float MachineGunPlayerDecorator::getMoveTimer()
{
	return player->getMoveTimer();
}

sf::RectangleShape MachineGunPlayerDecorator::getShape() const
{
	return player->getShape();
}

void MachineGunPlayerDecorator::setMoveTimer(float newTime)
{
	player->setMoveTimer(newTime);
}

void MachineGunPlayerDecorator::setHealth(int newHealth)
{
	player->setHealth(newHealth);
}

void MachineGunPlayerDecorator::setType(EntityType newType)
{
	player->setType(newType);
}

void MachineGunPlayerDecorator::decrementHealth()
{
	player->decrementHealth();
}

void MachineGunPlayerDecorator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);
}

void MachineGunPlayerDecorator::setItem(std::shared_ptr<IItem> newItem)
{
	player->setItem(newItem);
}

std::shared_ptr<IItem> MachineGunPlayerDecorator::getItem()
{
	return player->getItem();
}

void MachineGunPlayerDecorator::setDelayToShot(float newDelay)
{
	player->setDelayToShot(newDelay);
}
