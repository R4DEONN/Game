#include <iostream>
#include "GameScene.h"
#include "../Field/Field.h"
#include "../Entity/Player.h"
#include "../Entity/Enemy.h"
#include "../Utils/Utils.h"

GameScene::GameScene()
{
	music.openFromFile("../res/Overworld.wav");
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

void GameScene::clearField()
{
	enemies.clear();
	bullets.clear();

	player.movePlayerToCenter();
	spawner.restartSpawner();
}

void GameScene::restartGame()
{
	clearField();
	secondsToEnd = 100;
	player.restoreHealth();
}

bool GameScene::update(float elapsedSeconds)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gameState = GameState::PAUSE;
		music.pause();
	}
	if (gameState == GameState::PAUSE)
	{
		const int flag = pauseMenu.update(elapsedSeconds);
		if (flag == 0)
		{
			gameState = GameState::PLAYING;
			music.play();
		}
		else if (flag == 1)
		{
			restartGame();
			music.play();
			gameState = GameState::PLAYING;
		}
		else if (flag == 2)
		{
			return true;
		}
		return false;
	}
	if (gameState == GameState::STARTING)
	{
		const int flag = mainMenu.update(elapsedSeconds);
		if (flag == 0)
		{
			gameState = GameState::PLAYING;
			music.play();
		}
		else if (flag == 1)
		{
			return true;
		}
		return false;
	}
	if (gameState == GameState::LOSE)
	{
		const int flag = gameOverMenu.update(elapsedSeconds);
		if (flag == 0)
		{
			gameState = GameState::PLAYING;
			restartGame();
		}
		else if (flag == 1)
		{
			return true;
		}
		return false;
	}
	if (secondsToEnd >= 0)
	{
		secondsToEnd -= elapsedSeconds;
		spawner.Spawn(elapsedSeconds);
	}
	field.update(elapsedSeconds);
	overlay.update(secondsToEnd, player.getHealth());
	player.update(elapsedSeconds, field, bullets);
	updateBullets(elapsedSeconds);
	updateEnemies(elapsedSeconds);
	return false;
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (gameState == GameState::PAUSE)
	{
		target.draw(pauseMenu, states);
		return;
	}
	if (gameState == GameState::STARTING)
	{
		target.draw(mainMenu, states);
		return;
	}
	if (gameState == GameState::LOSE)
	{
		target.draw(gameOverMenu, states);
		return;
	}
	target.draw(field, states);
	target.draw(overlay, states);
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
				clearField();
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

void GameScene::updateEnemies(float elapsedSeconds)
{
	//TODO Улучшить код
	std::vector<int> indexesToDelete;
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

void GameScene::updateBullets(float elapsedSeconds)
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
