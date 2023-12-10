#include "MachineGunPlayerDecorator.h"

MachineGunPlayerDecorator::MachineGunPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	player->setDelayToShot(player->getDelayToShot() * 0.5);
}
