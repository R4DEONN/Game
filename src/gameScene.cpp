#include "gameScene.h"
#include "field.h"
#include "player.h"
#include "Enemy.h"

GameScene::GameScene()
{
	std::shared_ptr<Field> newField = std::make_shared<Field>();
	field = *newField;
	std::shared_ptr<Player> player = std::make_shared<Player>("../res/player.png", Field::getPlayerStartPosition());
	entities.push_back(player);
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(
		"../res/orc.png",
		sf::Vector2f(Field::getPlayerStartPosition().x - 100, Field::getPlayerStartPosition().y - 100)
	);
	entities.push_back(enemy);

	music.openFromFile("../res/Overworld.wav");
	music.play();
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
	field.update(elapsedSeconds);
	getPlayer()->update(elapsedSeconds, field, entities);
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
	for (int index : indexesToDelete)
	{
		auto entity = entities[index];
		entities.erase(entities.begin() + index);
		for (int indexToDelete : indexesToDelete)
		{
			if (indexToDelete > index)
			{
				--indexToDelete;
			}
		}
		entity.reset();
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
