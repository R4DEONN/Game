#include "player.h"
#include <SFML/Graphics.hpp>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window);
void handleEvents(sf::RenderWindow& window, Player* player);
void update(sf::Clock& clock, Player* player);
void render(sf::RenderWindow& window, Player* player);

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(
		sf::VideoMode::getDesktopMode(),
		"Journey of the Prairie King", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(MAX_FPS);
}

void handleEvents(sf::RenderWindow& window, Player* player)
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
			player->handleKeyPress(event.key);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			player->handleKeyRelease(event.key);
		}
	}
}

void update(sf::Clock& clock, Player* player)
{
	const float elapsedSeconds = clock.restart().asSeconds();
	player->update(elapsedSeconds);
}

void render(sf::RenderWindow& window, Player* player)
{
	window.clear(sf::Color::White);
	window.draw(player->getShape());
	window.display();
}

int main(int, char* [])
{
	sf::RenderWindow window;
	createWindow(window);

	std::unique_ptr<Player> player = std::make_unique<Player>();

	sf::Clock clock;
	while (window.isOpen())
	{
		handleEvents(window, player.get());
		update(clock, player.get());
		render(window, player.get());
	}

	return 0;
}