//TODO Выделить родителя

#ifndef GAME_GAMEOVERMENU_H
#define GAME_GAMEOVERMENU_H

#include "SFML/Graphics.hpp"
#include "Menu.h"

class GameOverMenu : public Menu
{
public:
	GameOverMenu();
private:
	sf::Text title;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_GAMEOVERMENU_H
