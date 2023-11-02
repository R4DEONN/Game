#include "player.h"
#include "field.h"
#include "bullet.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(
		sf::VideoMode::getDesktopMode(),
		"Journey of the Prairie King", sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow& window, Player& player, std::vector<Entity*>& entities)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			player.handleKeyPress(event.key);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			player.handleKeyRelease(event.key);
		}
	}
}

void update(sf::Clock& clock, Player& player, Field& field, std::vector<Entity*>& entities)
{
	const float elapsedSeconds = clock.getElapsedTime().asSeconds();
	clock.restart();
	player.update(elapsedSeconds, field, entities);
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
		Entity* entity = entities[index];
		entities.erase(entities.begin() + index);
		for (int i = 0; i < indexesToDelete.size(); ++i)
		{
			if (indexesToDelete[i] > index)
			{
				--indexesToDelete[i];
			}
		}
		delete entity;
	}
}

void render(sf::RenderWindow& window, Player& player, Field& field, std::vector<Entity*>& entities)
{
	window.clear();
	//TODO Убрать отрисовку через поле
	field.draw(window);
	std::vector<int> indexesToDelete;
	for (Entity* entity : entities)
	{
		window.draw(*entity);
	}
	window.draw(player);
	window.display();
}

int main(int, char* [])
{
	sf::RenderWindow window;
	createWindow(window);

	Field field;
	Player player("../res/player.png", Field::getPlayerStartPosition());

	std::vector<Entity*> entities;

	auto enemy = new Enemy(
		"../res/player.png",
		Field::getPlayerStartPosition()
		);
	entities.push_back(enemy);

	sf::Clock clock;
	while (window.isOpen())
	{
		handleEvents(window, player, entities);
		update(clock, player, field, entities);
		render(window, player, field, entities);
	}

	return 0;
}