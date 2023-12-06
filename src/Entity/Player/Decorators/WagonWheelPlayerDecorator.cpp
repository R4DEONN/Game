//
// Created by admin on 06.12.2023.
//

#include "WagonWheelPlayerDecorator.h"

WagonWheelPlayerDecorator::WagonWheelPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	this->player = player;
	this->player->setShootingType(ShootingType::EIGHT);
}
