#include "Spawner.h"
#include "../Field/Field.h"
#include "../Entity/Enemy.h"
#include "../Utils/Utils.h"

const constexpr float SPAWNER_COOLDOWN = 1.5;

const sf::Vector2f SPAWN_POINTS[] = {
	getFieldPoint(7, 0),
	getFieldPoint(8, 0),
	getFieldPoint(9, 0),
	getFieldPoint(15, 7),
	getFieldPoint(15, 8),
	getFieldPoint(15, 9),
	getFieldPoint(7, 15),
	getFieldPoint(8, 15),
	getFieldPoint(9, 15),
	getFieldPoint(0, 7),
	getFieldPoint(0, 8),
	getFieldPoint(0, 9),
};

Spawner::Spawner(std::vector<std::shared_ptr<Enemy>>& Enemies)
{
	enemies = &Enemies;
	timeToSpawn = SPAWNER_COOLDOWN;
}

void Spawner::Spawn(float elapsedSeconds)
{
	if (timeToSpawn > 0)
	{
		timeToSpawn -= elapsedSeconds;
		return;
	}
	timeToSpawn = SPAWNER_COOLDOWN;

	for (unsigned char i = 0; i < amountEnemiesToSpawn; ++i)
	{
		const auto index = randomer();
		const auto point = SPAWN_POINTS[index];
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
			"../res/orc.png",
			point
		);
		enemies->push_back(enemy);
	}
}

void Spawner::restartSpawner()
{
	timeToSpawn = 1.5;
}
