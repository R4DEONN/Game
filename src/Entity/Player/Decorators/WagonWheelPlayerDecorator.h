#ifndef GAME_WAGONWHEELPLAYERDECORATOR_H
#define GAME_WAGONWHEELPLAYERDECORATOR_H


#include "PlayerDecorator.h"

class WagonWheelPlayerDecorator : public PlayerDecorator
{
public:
	explicit WagonWheelPlayerDecorator(const std::shared_ptr<IPlayer>& player);
};


#endif //GAME_WAGONWHEELPLAYERDECORATOR_H
