#include "player.h"
#include "field.h"
#include "Enemy.h"
#include "gameScene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(
		sf::VideoMode::getDesktopMode(),
		"Journey of the Prairie King", sf::Style::Close, settings);
	window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void update(sf::Clock& clock, GameScene& scene)
{
	const float elapsedSeconds = clock.getElapsedTime().asSeconds();
	clock.restart();
	scene.getField().update(elapsedSeconds);
	scene.getPlayer().update(elapsedSeconds, scene.getField(), scene.getEntities());
	std::vector<int> indexesToDelete;
	for (int i = 0; i < scene.getEntities().size(); i++)
	{
		if (scene.getEntities()[i]->getIsAlive())
		{
			scene.getEntities()[i]->update(elapsedSeconds, scene.getField(), scene.getEntities());
		}
		else
		{
			indexesToDelete.push_back(i);
		}
	}
	for (int index : indexesToDelete)
	{
		auto entity = scene.getEntities()[index];
		scene.getEntities().erase(scene.getEntities().begin() + index);
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

void render(sf::RenderWindow& window, GameScene& scene)
{
	window.clear();
	//TODO Убрать отрисовку через поле
	scene.getField().draw(window);
	auto entities = scene.getEntities();
	for (auto entity : entities)
	{
		window.draw(*entity);
	}
	window.display();
}

int main(int, char* [])
{
	sf::RenderWindow window;
	createWindow(window);

	GameScene scene;

//	sf::Music music;
//	music.openFromFile("../res/Overworld.wav");
//	music.play();
//
//	Field field;
//	std::vector<Entity*> entities;
//
//	auto player = new Player("../res/player.png", Field::getPlayerStartPosition());
//	entities.push_back(player);
//
//	auto enemy = new Enemy(
//		"../res/orc.png",
//		{Field::getPlayerStartPosition().x - 100, Field::getPlayerStartPosition().y - 100}
//		);
//	entities.push_back(enemy);

	sf::Clock clock;
	while (window.isOpen())
	{
		handleEvents(window);
		update(clock, scene);
		render(window, scene);
	}

	return 0;
}