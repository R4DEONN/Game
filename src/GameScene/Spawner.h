#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "../Entity/Enemy/Enemy.h"
#include "../Utils/Randomer.h"
#include "../Entity/Enemy/EnemyCreator.h"
#include <memory>
#include <vector>

class Spawner
{
 public:
	explicit Spawner(std::vector<std::shared_ptr<IEnemy>>& Enemies);
	void Spawn(float elapsedSeconds);
	void restartSpawner();
 private:
	std::vector<std::shared_ptr<IEnemy>>* enemies;
	unsigned char amountEnemiesToSpawn = 4;
	float timeToSpawn;
	Randomer enemyTypeRandomer = {0, 0};
	Randomer pointRandomer = { 0, 11};
};

#endif //_SPAWNER_H_
