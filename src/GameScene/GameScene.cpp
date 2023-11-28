#include <iostream>
#include "GameScene.h"

GameScene::GameScene()
: entityManager(field)
{
	music.openFromFile("../res/Overworld.wav");
	music.setLoop(true);
}

void GameScene::restartGame()
{
	entityManager.restart();
	//TODO remove magic numbers
	secondsToEnd = 100;
	entityManager.getPlayer()->setHealth(3);
}

bool GameScene::update(float elapsedSeconds)
{
	auto player = entityManager.getPlayer();

	if (player->getHealth() < 0)
	{
		gameState = GameState::LOSE;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && gameState == GameState::PLAYING)
	{
		gameState = GameState::PAUSE;
		music.pause();
	}
	//TODO вынести логику в switch
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

	field.update(elapsedSeconds);
	overlay.update(secondsToEnd, player->getHealth(), elapsedSeconds);
	entityManager.update(elapsedSeconds, secondsToEnd);
	return false;
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	switch (gameState)
	{
	case GameState::PAUSE:
		target.draw(pauseMenu, states);
		break;
	case GameState::STARTING:
		target.draw(mainMenu, states);
		break;
	case GameState::LOSE:
		target.draw(gameOverMenu, states);
		break;
	default:
		target.draw(field, states);
		target.draw(overlay, states);
		entityManager.draw(target, states);
	}
}
