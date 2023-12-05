//
// Created by admin on 26.11.2023.
//

#ifndef GAME_MACHINEGUNPLAYERDECORATOR_H
#define GAME_MACHINEGUNPLAYERDECORATOR_H

#include "PlayerDecorator.h"

class MachineGunPlayerDecorator : public PlayerDecorator
{
public:
	explicit MachineGunPlayerDecorator(const std::shared_ptr<IPlayer>& player);
};


#endif //GAME_MACHINEGUNPLAYERDECORATOR_H
