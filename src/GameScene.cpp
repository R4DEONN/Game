#include <iostream>
#include "GameScene.h"
#include "Field/Field.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Utils/Utils.h"

GameScene::GameScene()
{
	music.openFromFile("../res/Overworld.wav");

	spawner.setEntities(entities);
	std::shared_ptr<Player> player = std::make_shared<Player>("../res/body.png", "../res/foot.png", getPlayerStartPosition());
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

void GameScene::setState(GameState newState)
{
	gameState = newState;
}

void GameScene::restartGame()
{
	const int entitiesSize = entities.size();
    std::cout << entitiesSize << std::endl;
	for (int i = 1; i < entitiesSize; i++)
	{
        std::cout << i << std::endl;
		entities.erase(entities.begin() + i);
	}
}

void GameScene::update(float elapsedSeconds)
{
	if (gameState == GameState::LOSE)
	{
		return;
	}
	spawner.Spawn(elapsedSeconds);
	field.update(elapsedSeconds);
	std::vector<int> indexesToDelete;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getHealth() >= 0)
		{
			entities[i]->update(elapsedSeconds, field, entities);
		}
		else
		{
            if (entities[i]->getType() == EntityType::PLAYER)
            {
                setState(GameState::LOSE);
            }
            else
            {
                indexesToDelete.push_back(i);
            }
		}
	}
	if (!handleCollision())
    {
        for (int i = indexesToDelete.size() - 1; i >= 0; --i)
        {
            entities.erase(entities.begin() + indexesToDelete[i]);
        }
    }
}

void GameScene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(field, states);
	for (const auto& entity : entities)
	{
		target.draw(*entity, states);
	}
}

bool GameScene::handleCollision()
{
	const auto player = getPlayer();
	const sf::FloatRect playerBounds = player->getShape().getGlobalBounds();
    for (const auto& entity : entities)
	{
		if (entity->getType() == EntityType::PLAYER
			|| entity->getType() == EntityType::BULLET)
		{
			continue;
		}

		const sf::FloatRect enemyBounds = entity->getShape().getGlobalBounds();
		if (playerBounds.intersects(enemyBounds))
		{
			player->decrementHealth();
			if (player->getHealth() < 0)
			{
				gameState = GameState::LOSE;
			}
			else
			{
				restartGame();
			}
			return true;
		}
	}
	return false;
}
