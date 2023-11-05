#include "Spawner.h"
#include "field.h"
#include "Enemy.h"

const sf::Vector2f SPAWN_POINTS[] = {
	Field::getFieldPoint(7, 0),
	Field::getFieldPoint(8, 0),
	Field::getFieldPoint(9, 0),
	Field::getFieldPoint(15, 7),
	Field::getFieldPoint(15, 8),
	Field::getFieldPoint(15, 9),
	Field::getFieldPoint(7, 15),
	Field::getFieldPoint(8, 15),
	Field::getFieldPoint(9, 15),
	Field::getFieldPoint(0, 7),
	Field::getFieldPoint(0, 8),
	Field::getFieldPoint(0, 9),
};

Spawner::Spawner(std::vector<std::shared_ptr<Entity>>& Entities)
{
	entities = &Entities;
}

void Spawner::Spawn(float elapsedSeconds)
{
	if (timeToSpawn > 0)
	{
		timeToSpawn -= elapsedSeconds;
		return;
	}

	timeToSpawn = 1;

	for (unsigned char i = 0; i < amountEnemiesToSpawn; ++i)
	{
		const auto index = randomer();
		const auto point = SPAWN_POINTS[index];
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
			"../res/orc.png",
			point
		);
		entities->push_back(enemy);
	}
}

