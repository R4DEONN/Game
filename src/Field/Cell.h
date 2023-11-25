#ifndef _CELL_H_
#define _CELL_H_

#include "SFML/Graphics.hpp"

enum struct CellCategory
{
	WALL,
	SAND,
	BONES,
	BLOOD,
	STONES,
	GRASS,
};

class Cell : public sf::Drawable
{
 public:
	Cell(CellCategory Category, sf::Vector2f position, sf::Vector2f size);
	CellCategory getCategory();
	sf::RectangleShape& getBounds();
 private:
	CellCategory category;
	sf::RectangleShape bounds;
	sf::Texture texture;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //_CELL_H_
