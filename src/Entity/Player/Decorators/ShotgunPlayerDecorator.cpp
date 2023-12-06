#include "ShotgunPlayerDecorator.h"

ShotgunPlayerDecorator::ShotgunPlayerDecorator(const std::shared_ptr<IPlayer>& player)
	: PlayerDecorator(player)
{
	this->player = player;
	this->player->setShootingType(ShootingType::TRIPLE);
}