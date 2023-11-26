//
// Created by admin on 26.11.2023.
//

#ifndef GAME_RANDOMER_H
#define GAME_RANDOMER_H

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

#endif //GAME_RANDOMER_H
