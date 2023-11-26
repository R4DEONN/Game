//
// Created by admin on 14.11.2023.
//

#ifndef GAME_OVERLAY_H
#define GAME_OVERLAY_H

#include <SFML/Graphics.hpp>

class Overlay : public sf::Drawable
{
public:
	Overlay(float SecondsToEnd, int PlayerHealth);
	void update(float secondsToEnd, int playerHealth);
private:
	sf::Texture healthTexture;
	sf::RectangleShape healthShape;
	sf::Texture clockTexture;
	sf::RectangleShape clockShape;
	sf::RectangleShape timeLine;
	sf::Texture currentItemFieldTexture;
	sf::RectangleShape currentItemField;
	sf::Font font;
	sf::Text healthPoints;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //GAME_OVERLAY_H
