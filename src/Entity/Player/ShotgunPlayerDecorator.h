#ifndef GAME_SHOTGUNPLAYERDECORATOR_H
#define GAME_SHOTGUNPLAYERDECORATOR_H


#include "PlayerDecorator.h"

class ShotgunPlayerDecorator : public PlayerDecorator
{
public:
	explicit ShotgunPlayerDecorator(const std::shared_ptr<IPlayer>& player);
};


#endif //GAME_SHOTGUNPLAYERDECORATOR_H
