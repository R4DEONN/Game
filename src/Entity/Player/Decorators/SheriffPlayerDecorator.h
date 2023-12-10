#ifndef GAME_SHERIFFPLAYERDECORATOR_H
#define GAME_SHERIFFPLAYERDECORATOR_H


#include "PlayerDecorator.h"

class SheriffPlayerDecorator : public PlayerDecorator
{
public:
	explicit SheriffPlayerDecorator(const std::shared_ptr<IPlayer>& player);
};


#endif //GAME_SHERIFFPLAYERDECORATOR_H
