//
// Created by admin on 28.11.2023.
//

#ifndef GAME_MULTIPLICATIONENTITYMANAGER_H
#define GAME_MULTIPLICATIONENTITYMANAGER_H


#include <memory>
#include <vector>
#include "Enemy.h"
#include "Bullet.h"
#include "../Utils/Utils.h"
#include "../GameScene/Spawner.h"
#include "../Utils/Randomer.h"

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
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<IItem>> items;
	std::shared_ptr<IPlayer> player = std::make_shared<Player>(3, getCenterCoordinates());
	Spawner spawner = Spawner(enemies);
	Randomer itemTypeRandomer = {1, 4};
	Randomer itemDropRandomer = {0, 100};

	void takeItem(const std::shared_ptr<IItem>& item);
	void useItem(ItemType itemType);
	void updateEnemies(float elapsedSeconds);
	void updateBullets(float elapsedSeconds);
	bool handleCollision();
	void spawnItemWithChance(sf::Vector2f position);
};


#endif //GAME_MULTIPLICATIONENTITYMANAGER_H
