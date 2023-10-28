#include "player.h"
#include "field.h"
#include <SFML/Graphics.hpp>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window);
void handleEvents(sf::RenderWindow& window, Player* player);
void update(sf::Clock& clock, Player* player);
void render(sf::RenderWindow& window, Player* player, Field* field);

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(
		sf::VideoMode::getDesktopMode(),
		"Journey of the Prairie King", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow& window, Player& player)
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

void update(sf::Clock& clock, Player& player, Field& field)
{
	const float elapsedSeconds = clock.getElapsedTime().asSeconds();
	clock.restart();
	player.update(elapsedSeconds, field);
}

void render(sf::RenderWindow& window, Player& player, Field& field)
{
	window.clear();
	//TODO Убрать отрисовку через поле
	field.draw(window);
	window.draw(player);
	window.display();
}

int main(int, char* [])
{
	sf::RenderWindow window;
	createWindow(window);

	Field field;
	Player player(Field::getPlayerStartPosition());

	sf::Clock clock;
	while (window.isOpen())
	{
		handleEvents(window, player);
		update(clock, player, field);
		render(window, player, field);
	}

	return 0;
}