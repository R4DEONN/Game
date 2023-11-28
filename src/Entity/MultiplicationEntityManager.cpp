#include "MultiplicationEntityManager.h"
#include "../Item/ItemCreator.h"
#include "Player/FastPlayerDecorator.h"
#include "Player/MachineGunPlayerDecorator.h"
#include "Player/ShotgunPlayerDecorator.h"

MultiplicationEntityManager::MultiplicationEntityManager(Field& field)
: field(field)
{}

void MultiplicationEntityManager::update(float elapsedSeconds, float& secondsToEnd)
{
	auto item = player->getItem();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && item)
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
	if (itemDropRandomer() < 10)
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
			if (player->getHealth() < 0)
			{
				//TODO fix
//				gameState = GameState::LOSE;
			}
			else
			{
				restart();
			}
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
	switch (itemType)
	{
	case ItemType::COFFEE:
		player = std::make_shared<FastPlayerDecorator>(player);
		break;
	case ItemType::MACHINE_GUN:
		player = std::make_shared<MachineGunPlayerDecorator>(player);
		break;
	case ItemType::SHOTGUN:
		player = std::make_shared<ShotgunPlayerDecorator>(player);
		break;
	default:
		break;
	}

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
