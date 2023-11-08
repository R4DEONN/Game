#include "gameScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr const unsigned ANTIALIASING_LEVEL = 8;
constexpr const unsigned MAX_FPS = 60;

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
	scene.update(elapsedSeconds);
}

void render(sf::RenderWindow& window, GameScene& scene)
{
	window.clear();
	//TODO Убрать отрисовку через поле
	window.draw(scene);
	window.display();
}

int main(int, char* [])
{
	sf::RenderWindow window;
	createWindow(window);

	GameScene scene;

	sf::Clock clock;
	while (window.isOpen())
	{
		handleEvents(window);
		update(clock, scene);
		render(window, scene);
	}

	return 0;
}