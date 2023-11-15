//TODO Выделить родителя

#ifndef GAME_GAMEOVERMENU_H
#define GAME_GAMEOVERMENU_H

#include <SFML/Graphics.hpp>

class GameOverMenu : public sf::Drawable
{
public:
	GameOverMenu();
	int update();
private:
	sf::ConvexShape triangle;
	sf::Font font;
	sf::Text endGame;
	sf::Text again;
	sf::Text exit;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_GAMEOVERMENU_H
