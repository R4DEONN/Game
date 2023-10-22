#include <SFML/Graphics.hpp>

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow& window);
void initializePackman(sf::CircleShape& shape);
void handleEvents(sf::RenderWindow& window);
void update(sf::Clock& clock, sf::CircleShape& shape);
void render(sf::RenderWindow& window, sf::CircleShape& shape);

void createWindow(sf::RenderWindow& window)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Journey of the Prairie King", sf::Style::Default, settings);
	window.setFramerateLimit(MAX_FPS);
}

void initializePlayer(sf::CircleShape& shape)
{
	shape.setRadius(20);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 0);
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

void update(sf::Clock& clock)
{
	const float elapsedTime = clock.getElapsedTime().asSeconds();
	clock.restart();
	//updateGameScene(scene, elapsedTime);
}

void render(sf::RenderWindow& window)
{
	window.clear();
	//drawGameScene(window, scene);
	window.display();
}

int main(int, char* [])
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(800, 800), "Journey of the Prairie King Game Clone", sf::Style::Close, settings);

	sf::Clock clock;
//	GameScene scene;
//	initializeGameScene(scene, sf::Vector2f(window.getSize()));

	while (window.isOpen())
	{
		handleEvents(window);
		update(clock);
//		window.setTitle(getGameSceneWindowTitle(scene));
		render(window);
	}

	return 0;
}