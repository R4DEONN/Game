#include "WagonWheelPlayerDecorator.h"

WagonWheelPlayerDecorator::WagonWheelPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	this->player = player;
	this->player->setShootingType(ShootingType::EIGHT);
}
