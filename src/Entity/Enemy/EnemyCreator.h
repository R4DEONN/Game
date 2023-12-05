//
// Created by admin on 05.12.2023.
//

#ifndef GAME_ENEMYCREATOR_H
#define GAME_ENEMYCREATOR_H


#include <memory>
#include "IEnemy.h"
#include "EnemyType.h"

class EnemyCreator
{
public:
	static std::shared_ptr<IEnemy> createEnemy(EnemyType type, sf::Vector2f position);
};


#endif //GAME_ENEMYCREATOR_H
