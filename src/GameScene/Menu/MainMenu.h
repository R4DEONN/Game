//
// Created by admin on 15.11.2023.
//

#ifndef GAME_MAINMENU_H
#define GAME_MAINMENU_H

#include "SFML/Graphics.hpp"
#include "Menu.h"

class MainMenu : public Menu
{
public:
	MainMenu(const std::wstring strings[], int count);
private:
	sf::Texture logoTexture;
	sf::RectangleShape logoShape;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_MAINMENU_H
