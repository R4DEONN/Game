#include <iostream>
#include "GameScene.h"
#include "Field/Field.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Utils/Utils.h"

GameScene::GameScene()
{
	music.openFromFile("../res/Overworld.wav");

	music.play();
	music.setLoop(true);
}

std::vector<std::shared_ptr<Enemy>>& GameScene::getEnemies()
{
	return enemies;
}

std::vector<std::shared_ptr<Bullet>>& GameScene::getBullets()
{
	return bullets;
}

Player& GameScene::getPlayer()
{
	return player;
}

Field& GameScene::getField()
{
	return field;
}

void GameScene::setState(GameState newState)
{
	gameState = newState;
}

void GameScene::restartGame()
{
	enemies.clear();
	bullets.clear();

	player.movePlayerToCenter();
	spawner.restartSpawner();
}

void GameScene::update(float elapsedSeconds)
{
	if (gameState == GameState::LOSE)
	{
		return;
	}
	spawner.Spawn(elapsedSeconds);
	field.update(elapsedSeconds);
	if (player.getHealth() < 0)
	{
		setState(GameState::LOSE);
	}
	else
	{
		player.update(elapsedSeconds, field, bullets);
	}
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
	indexesToDelete.clear();
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getHealth() >= 0)
		{
			enemies[i]->update(elapsedSeconds, field, enemies, player);
		}
		else
		{
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

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(field, states);
	target.draw(player, states);
	for (const auto& bullet: bullets)
	{
		target.draw(*bullet, states);
	}
	for (const auto& enemy: enemies)
	{
		target.draw(*enemy, states);
	}
}

bool GameScene::handleCollision()
{
	const sf::FloatRect playerBounds = player.getShape().getGlobalBounds();
	for (const auto& enemy: enemies)
	{
		const sf::FloatRect enemyBounds = enemy->getShape().getGlobalBounds();
		if (playerBounds.intersects(enemyBounds))
		{
			player.decrementHealth();
			if (player.getHealth() < 0)
			{
				gameState = GameState::LOSE;
			}
			else
			{
				restartGame();
			}
			return true;
		}
		for (const auto& bullet: bullets)
		{
			const auto bulletBound = bullet->getShape().getGlobalBounds();
			if (bulletBound.intersects(enemyBounds))
			{
				bullet->decrementHealth();
				enemy->decrementHealth();
				return true;
			}
		}
	}
	return false;
}
