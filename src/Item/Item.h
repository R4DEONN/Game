//
// Created by admin on 22.11.2023.
//

#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <SFML/Graphics.hpp>

class Item : public sf::Drawable
{
public:
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_ITEM_H
