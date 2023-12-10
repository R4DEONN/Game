#include "FastPlayerDecorator.h"
#include "../../../Common/GameConstants.h"

FastPlayerDecorator::FastPlayerDecorator(const std::shared_ptr<IPlayer>& player)
: PlayerDecorator(player)
{
	player->setSpeed(player->getSpeed() * 1.5);
}

void FastPlayerDecorator::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets)
{}
