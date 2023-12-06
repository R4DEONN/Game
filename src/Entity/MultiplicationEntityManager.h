#ifndef GAME_MULTIPLICATIONENTITYMANAGER_H
#define GAME_MULTIPLICATIONENTITYMANAGER_H

#include <memory>
#include <vector>
#include "Enemy/Enemy.h"
#include "Bullet.h"
#include "../Utils/Utils.h"
#include "../GameScene/Spawner.h"
#include "../Utils/Randomer.h"

static const constexpr int DEFAULT_PLAYER_HP = 3;

class MultiplicationEntityManager
{
public:
	explicit MultiplicationEntityManager(Field& field);
	void update(float elapsedSeconds, float& secondsToEnd);
	void restart();
	std::shared_ptr<IPlayer> getPlayer();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	Field& field;
	std::vector<std::shared_ptr<IEnemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<IItem>> items;
	std::vector<ItemType> decoratorsList{};
	std::map<ItemType, float> decoratorsDuration{};
	std::shared_ptr<IPlayer> player = std::make_shared<Player>(3, getCenterCoordinates());
	Spawner spawner = Spawner(enemies);
	Randomer itemTypeRandomer = {1, 5};
	Randomer itemDropRandomer = {0, 5};

	void decoratePlayer();
	void removeDecorator(ItemType itemType);
	void takeItem(const std::shared_ptr<IItem>& item);
	void useItem(ItemType itemType);
	void updateEnemies(float elapsedSeconds);
	void updateBullets(float elapsedSeconds);
	bool handleCollision();
	void spawnItemWithChance(sf::Vector2f position);
};

#endif //GAME_MULTIPLICATIONENTITYMANAGER_H
