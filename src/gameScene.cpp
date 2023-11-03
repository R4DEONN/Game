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

Entity& GameScene::getPlayer()
{
	return *entities[0];
}

Field& GameScene::getField()
{
	return field;
}