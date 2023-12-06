#include "MultiplicationEntityManager.h"
#include "../Item/ItemCreator.h"
#include "Player/decorators/FastPlayerDecorator.h"
#include "Player/decorators/MachineGunPlayerDecorator.h"
#include "Player/decorators/ShotgunPlayerDecorator.h"
#include "Player/Decorators/WagonWheelPlayerDecorator.h"

constexpr const float ITEM_DURATION = 10.f;

MultiplicationEntityManager::MultiplicationEntityManager(Field& field)
: field(field)
{}

void MultiplicationEntityManager::update(float elapsedSeconds, float& secondsToEnd)
{
	for (auto& duration : decoratorsDuration)
	{
		duration.second -= elapsedSeconds;
		if (duration.second <= 0)
		{
			duration.second = 0;
		}
	}

	for (auto decorator : decoratorsList)
	{
		if (decoratorsDuration[decorator] == 0)
		{
			removeDecorator(decorator);
		}
	}

	auto item = player->getItem();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && item->getType() != ItemType::NONE)
	{
		useItem(item->getType());
	}

	if (secondsToEnd >= 0)
	{
		secondsToEnd -= elapsedSeconds;
		spawner.Spawn(elapsedSeconds);
	}
	player->update(elapsedSeconds, field, bullets);
	updateBullets(elapsedSeconds);
	updateEnemies(elapsedSeconds);
}

void MultiplicationEntityManager::restart()
{
	enemies.clear();
	bullets.clear();
	items.clear();

	decoratorsList.clear();
	for (auto decoratorDuration : decoratorsDuration)
	{
		decoratorDuration.second = 0;
	}
//	decoratePlayer();
	player = std::make_shared<Player>(player->getHealth(), getCenterCoordinates());
	spawner.restartSpawner();
}

std::shared_ptr<IPlayer> MultiplicationEntityManager::getPlayer()
{
	return player;
}

void MultiplicationEntityManager::updateEnemies(float elapsedSeconds)
{
	//TODO Улучшить код
	std::vector<int> indexesToDelete;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getHealth() >= 0)
		{
			sf::Vector2f playerPosition = player->getPosition();
			enemies[i]->update(elapsedSeconds, field, enemies, playerPosition);
		}
		else
		{
			spawnItemWithChance(enemies[i]->getPosition());
			indexesToDelete.push_back(i);
		}
	}
	if (!handleCollision())
	{
		for (int i = indexesToDelete.size() - 1; i >= 0; --i)
		{
			enemies.erase(enemies.begin() + indexesToDelete[i]);
		}
	}
}

void MultiplicationEntityManager::updateBullets(float elapsedSeconds)
{
	std::vector<int> indexesToDelete;
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getHealth() >= 0)
		{
			bullets[i]->update(elapsedSeconds, field);
		}
		else
		{
			indexesToDelete.push_back(i);
		}
	}
	for (int i = indexesToDelete.size() - 1; i >= 0; --i)
	{
		bullets.erase(bullets.begin() + indexesToDelete[i]);
	}
}

void MultiplicationEntityManager::spawnItemWithChance(sf::Vector2f position)
{
	if (itemDropRandomer() < 5)
	{
		auto itemType = ItemType(itemTypeRandomer());
		items.push_back(ItemCreator::createItem(itemType, position));
	}
}

bool MultiplicationEntityManager::handleCollision()
{
	const sf::FloatRect playerBounds = player->getShape().getGlobalBounds();
	for (const auto& enemy: enemies)
	{
		const sf::FloatRect enemyBounds = enemy->getShape().getGlobalBounds();
		if (playerBounds.intersects(enemyBounds))
		{
			player->setHealth(player->getHealth() - 1);
			restart();
			return true;
		}
		for (const auto& bullet: bullets)
		{
			const auto bulletBound = bullet->getShape().getGlobalBounds();
			if (bulletBound.intersects(enemyBounds))
			{
				bullet->setHealth(bullet->getHealth() - 1);
				enemy->setHealth(enemy->getHealth() - 1);
				return true;
			}
		}
	}
	for (int i = 0; i < items.size(); i++)
	{
		const sf::FloatRect itemBounds = items[i]->getImmutableShape().getGlobalBounds();
		if (playerBounds.intersects(itemBounds))
		{
			takeItem(items[i]);
			items.erase(items.begin() + i);
		}
	}
	return false;
}

void MultiplicationEntityManager::takeItem(const std::shared_ptr<IItem>& item)
{
	switch (item->getType())
	{
	case ItemType::EXTRA_HP:
		player->setHealth(player->getHealth() + 1);
		break;
	default:
		player->setItem(item);
	}
}

void MultiplicationEntityManager::useItem(ItemType itemType)
{
	if (std::find(decoratorsList.begin(), decoratorsList.end(), itemType) == decoratorsList.end())
	{
		decoratorsList.push_back(itemType);
	}
	decoratorsDuration[itemType] = ITEM_DURATION;
	decoratePlayer();
	player->setItem(std::make_shared<Item>(sf::Vector2f{0, 0}));
}

void MultiplicationEntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*player, states);
	for (const auto& item: items)
	{
		target.draw(*item, states);
	}
	for (const auto& bullet: bullets)
	{
		target.draw(*bullet, states);
	}
	for (const auto& enemy: enemies)
	{
		target.draw(*enemy, states);
	}
}

void MultiplicationEntityManager::removeDecorator(ItemType itemType)
{
	auto it = std::remove(decoratorsList.begin(), decoratorsList.end(), itemType);
	decoratorsList.erase(it, decoratorsList.end());
	decoratePlayer();
}

void MultiplicationEntityManager::decoratePlayer()
{
	player = std::make_shared<Player>(player->getHealth(), player->getPosition());
	for (auto decorator : decoratorsList)
	{
		switch (decorator)
		{
		case ItemType::COFFEE:
			player = std::make_shared<FastPlayerDecorator>(player);
			continue;
		case ItemType::MACHINE_GUN:
			player = std::make_shared<MachineGunPlayerDecorator>(player);
			continue;
		case ItemType::SHOTGUN:
			player = std::make_shared<ShotgunPlayerDecorator>(player);
			continue;
		case ItemType::WAGON_WHEEL:
			player = std::make_shared<WagonWheelPlayerDecorator>(player);
		case ItemType::EXTRA_HP:
		default:
			continue;
		}
	}
}
