#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "Entity/Entity.h"
#include "Entity/Enemy.h"
#include <memory>
#include <vector>
#include <random>
#include <chrono>

class Randomer {
	std::mt19937 gen_;
	std::uniform_int_distribution<size_t> dist_;
 public:
	Randomer(size_t min, size_t max, unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count())
		: gen_{seed}, dist_{min, max} {
	}

	size_t operator()() {
		return dist_(gen_);
	}
};

class Spawner
{
 public:
	explicit Spawner(std::vector<std::shared_ptr<Enemy>>& Enemies);
	void Spawn(float elapsedSeconds);
	void restartSpawner();
 private:
	std::vector<std::shared_ptr<Enemy>>* enemies;
	unsigned char amountEnemiesToSpawn = 2;
	float timeToSpawn = 1.5;
	Randomer randomer = {0, 11};
};

#endif //_SPAWNER_H_
