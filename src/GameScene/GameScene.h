#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../Field/Field.h"
#include "Spawner.h"
#include "../Entity/Player/Player.h"
#include "../Utils/Utils.h"
#include "../Entity/Enemy.h"
#include "../Entity/Bullet.h"
#include "./Overlay.h"
#include <vector>
#include "SFML/Audio.hpp"
#include "Menu/MainMenu.h"
#include "Menu/GameOverMenu.h"
#include "../Item/IItem.h"
#include "../Entity/MultiplicationEntityManager.h"

const std::wstring MAIN_MENU_MESSAGES[] = {
	L"Начать игру",
	L"Выйти из игры"
};

const std::wstring PAUSE_MENU_MESSAGES[] = {
	L"Продолжить игру",
	L"Заново",
	L"Выйти из игры"
};

enum class GameState
{
	STARTING,
	PLAYING,
	PAUSE,
	LOSE
};

 class GameScene : public sf::Drawable
{
 public:
	GameScene();
	void restartGame();
	bool update(float elapsedSeconds);

 private:
	MainMenu mainMenu = MainMenu(MAIN_MENU_MESSAGES, 2);
	MainMenu pauseMenu = MainMenu(PAUSE_MENU_MESSAGES, 3);
	GameOverMenu gameOverMenu;
	float secondsToEnd = 100;
	sf::Music music;
	Field field;
	MultiplicationEntityManager entityManager;
	GameState gameState = GameState::STARTING;
	Overlay overlay = Overlay(secondsToEnd, entityManager.getPlayer()->getHealth());

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //_GAMESCENE_H_
