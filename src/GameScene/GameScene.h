#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../Field/Field.h"
#include "../Entity/Entity.h"
#include "Spawner.h"
#include "../Entity/Player.h"
#include "../Utils/Utils.h"
#include "../Entity/Enemy.h"
#include "../Entity/Bullet.h"
#include "./Overlay.h"
#include <vector>
#include "SFML/Audio.hpp"
#include "Menu/MainMenu.h"
#include "Menu/GameOverMenu.h"

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
	std::vector<std::shared_ptr<Enemy>>& getEnemies();
	std::vector<std::shared_ptr<Bullet>>& getBullets();
	Player& getPlayer();
	Field& getField();
	void setState(GameState newState);
	void clearField();
	void restartGame();
	bool update(float elapsedSeconds);

 private:
	MainMenu mainMenu = MainMenu(MAIN_MENU_MESSAGES, 2);
	MainMenu pauseMenu = MainMenu(PAUSE_MENU_MESSAGES, 3);
	GameOverMenu gameOverMenu;
	float secondsToEnd = 100;
	sf::Music music;
	Field field;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> bullets;
	Player player = Player("../res/body.png", "../res/foot.png", getCenterCoordinates());
	GameState gameState = GameState::STARTING;
	Overlay overlay = Overlay(secondsToEnd, player.getHealth());
	Spawner spawner = Spawner(enemies);

	void updateEnemies(float elapsedSeconds);
	void updateBullets(float elapsedSeconds);
    bool handleCollision();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //_GAMESCENE_H_
