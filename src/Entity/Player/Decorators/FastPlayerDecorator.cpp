#include "FastPlayerDecorator.h"
#include "../../../Common/GameConstants.h"

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
