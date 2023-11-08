#include "gameScene.h"
#include "field.h"
#include "player.h"
#include "Enemy.h"
#include "utils.h"

GameScene::GameScene()
{
	music.openFromFile("../res/Overworld.wav");

	spawner.setEntities(entities);
	std::shared_ptr<Player> player = std::make_shared<Player>("../res/player.png", getPlayerStartPosition());
	entities.push_back(player);

	music.play();
	music.setLoop(true);
}

std::vector<std::shared_ptr<Entity>>& GameScene::getEntities()
{
	return entities;
}

std::shared_ptr<Entity> GameScene::getPlayer()
{
	return entities[0];
}

Field& GameScene::getField()
{
	return field;
}

void GameScene::update(float elapsedSeconds)
{
	spawner.Spawn(elapsedSeconds);
	field.update(elapsedSeconds);
	std::vector<int> indexesToDelete;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getIsAlive())
		{
			entities[i]->update(elapsedSeconds, field, entities);
		}
		else
		{
			indexesToDelete.push_back(i);
		}
	}
	for (int i = indexesToDelete.size() - 1; i >= 0; --i)
	{
		entities.erase(entities.begin() + indexesToDelete[i]);
	}
}

void GameScene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(field, states);
	for (auto entity : entities)
	{
		target.draw(*entity, states);
	}
}
