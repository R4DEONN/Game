//
// Created by admin on 15.11.2023.
//

#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <SFML/Graphics.hpp>
#include <memory>

class Menu : public sf::Drawable
{
public:
	explicit Menu(const std::wstring* strings, int count);
	int update();

protected:
	std::vector<std::shared_ptr<sf::Text>> texts;
	sf::ConvexShape triangle;

private:
	sf::Font font;
	int selectedId;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_MENU_H
