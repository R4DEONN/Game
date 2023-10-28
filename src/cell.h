#ifndef _CELL_H_
#define _CELL_H_

#include <SFML/Graphics.hpp>

enum struct CellCategory
{
	WALL,
	PRAIRIE,
};

class Cell : public sf::Drawable
{
 public:
	Cell(CellCategory category, sf::Vector2f position, sf::Vector2f size, sf::Color color);
	CellCategory getCategory() const;
	sf::RectangleShape getBounds() const;
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	CellCategory category;
	sf::RectangleShape bounds;
};

#endif //_CELL_H_
