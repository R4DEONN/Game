#include "SheriffPlayerDecorator.h"

SheriffPlayerDecorator::SheriffPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	player->setShootingType(ShootingType::TRIPLE);
	player->setDelayToShot(player->getDelayToShot() * 0.75);
	player->setSpeed(player->getSpeed() * 1.25);
}
