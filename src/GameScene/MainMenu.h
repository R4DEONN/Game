//
// Created by admin on 15.11.2023.
//

#ifndef GAME_MAINMENU_H
#define GAME_MAINMENU_H

#include <SFML/Graphics.hpp>

class MainMenu : public sf::Drawable
{
public:
	MainMenu();
	int update();
private:
	sf::ConvexShape triangle;
	sf::Texture logoTexture;
	sf::RectangleShape logoShape;
	sf::Font font;
	sf::Text beginGame;
	sf::Text exitGame;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_MAINMENU_H
