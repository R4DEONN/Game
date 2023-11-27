#include "MachineGunPlayerDecorator.h"
#include "../../Common/GameConstants.h"

MachineGunPlayerDecorator::MachineGunPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	this->player = player;
	this->player->setDelayToShot(0.15);
}
