#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "Field/Field.h"
#include "Entity/Entity.h"
#include "Spawner.h"
#include <vector>
#include <SFML/Audio.hpp>

enum class GameState
{
	STARTING,
	PLAYING,
	RESTARTING,
	LOSE
};

 class GameScene : public sf::Drawable
{
 public:
	GameScene();
	std::vector<std::shared_ptr<Entity>>& getEntities();
	std::shared_ptr<Entity> getPlayer();
	Field& getField();
	void setState(GameState newState);
	void restartGame();

	void update(float elapsedSeconds);
 private:
	sf::Music music;
	Field field;
	std::vector<std::shared_ptr<Entity>> entities;
	GameState gameState = GameState::PLAYING;
	Spawner spawner;

    bool handleCollision();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //_GAMESCENE_H_