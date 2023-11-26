#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "../Entity/Enemy.h"
#include "../Utils/Randomer.h"
#include <memory>
#include <vector>

class Spawner
{
 public:
	explicit Spawner(std::vector<std::shared_ptr<Enemy>>& Enemies);
	void Spawn(float elapsedSeconds);
	void restartSpawner();
 private:
	std::vector<std::shared_ptr<Enemy>>* enemies;
	unsigned char amountEnemiesToSpawn = 2;
	float timeToSpawn;
	Randomer randomer = {0, 11};
};

#endif //_SPAWNER_H_
