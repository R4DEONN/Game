#include <iostream>
#include "GameScene.h"

const constexpr float GAME_DURATION = 100;

GameScene::GameScene()
: entityManager(field)
{
	music.openFromFile("../res/Overworld.wav");
	music.setLoop(true);
}

void GameScene::restartGame()
{
	entityManager.restart();
	secondsToEnd = GAME_DURATION;
	entityManager.getPlayer()->setHealth(DEFAULT_PLAYER_HP);
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

	bool isExitFromGame = false;
	switch (gameState)
	{
	case GameState::PAUSE:
		isExitFromGame = updatePauseMenu(elapsedSeconds);
		break;
	case GameState::STARTING:
		isExitFromGame = updateMainMenu(elapsedSeconds);
		break;
	case GameState::LOSE:
		isExitFromGame = updateGameOverMenu(elapsedSeconds);
		break;
	case GameState::PLAYING:
		field.update(elapsedSeconds);
		overlay.update(secondsToEnd, player->getHealth(), elapsedSeconds);
		entityManager.update(elapsedSeconds, secondsToEnd);
	}

	return isExitFromGame;
}

bool GameScene::updatePauseMenu(float elapsedSeconds)
{
	const int flag = pauseMenu.update(elapsedSeconds);
	switch (flag)
	{
	case 0:
		gameState = GameState::PLAYING;
		music.play();
		break;
	case 1:
		restartGame();
		music.play();
		gameState = GameState::PLAYING;
		break;
	case 2:
		return true;
	}

	return false;
}

bool GameScene::updateMainMenu(float elapsedSeconds)
{
	const int flag = mainMenu.update(elapsedSeconds);
	switch (flag)
	{
	case 0:
		gameState = GameState::PLAYING;
		music.play();
		break;
	case 1:
		return true;
	}

	return false;
}

bool GameScene::updateGameOverMenu(float elapsedSeconds)
{
	const int flag = gameOverMenu.update(elapsedSeconds);
	switch (flag)
	{
	case 0:
		gameState = GameState::PLAYING;
		restartGame();
		break;
	case 1:
		return true;
	}

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
