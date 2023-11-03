#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "field.h"
#include "entity.h"
#include <vector>
#include <SFML/Audio.hpp>

enum class GameState
{
	STARTING,
	PLAYING,
	RESTARTING,
	LOSE
};

class GameScene
{
 public:
	GameScene();
	std::vector<std::shared_ptr<Entity>>& getEntities();
	Entity& getPlayer();
	Field& getField();
 private:
	sf::Music music;
	Field field;
	std::vector<std::shared_ptr<Entity>> entities;
	GameState gameState = GameState::PLAYING;
};

#endif //_GAMESCENE_H_
