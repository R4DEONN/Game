#ifndef GAME_FASTPLAYERDECORATOR_H
#define GAME_FASTPLAYERDECORATOR_H

#include "PlayerDecorator.h"

class FastPlayerDecorator : public PlayerDecorator
{
public:
	explicit FastPlayerDecorator(const std::shared_ptr<IPlayer>& player);
	void update(float elapsedTime, Field &field, std::vector<std::shared_ptr<Bullet>> &bullets) override;
};


#endif //GAME_FASTPLAYERDECORATOR_H
