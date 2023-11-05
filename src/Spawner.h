#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "entity.h"
#include <memory>
#include <vector>
#include <random>

class Randomer {
	std::mt19937 gen_;
	std::uniform_int_distribution<size_t> dist_;
 public:
	Randomer(size_t min, size_t max, unsigned int seed = std::random_device{}())
		: gen_{seed}, dist_{min, max} {
	}

	size_t operator()() {
		return dist_(gen_);
	}
};

class Spawner
{
 public:
	explicit Spawner(std::vector<std::shared_ptr<Entity>>& Entities);
	void Spawn(float elapsedSeconds);
 private:
	std::vector<std::shared_ptr<Entity>>* entities;
	unsigned char amountEnemiesToSpawn = 2;
	float timeToSpawn = 1;
	Randomer randomer{0, 11};
};

#endif //_SPAWNER_H_
