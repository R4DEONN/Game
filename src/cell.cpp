#include "cell.h"
#include "gameConstants.h"

Cell::Cell(CellCategory Category, sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	category = Category;
	bounds.setPosition(position);
	bounds.setSize(size);
	if (category == CellCategory::WALL)
	{
		texture.loadFromFile("../res/Tree.png");
		bounds.setTexture(&texture);
		bounds.setTextureRect(sf::IntRect(0, 0, GameConstants::BLOCK_SIZE, GameConstants::BLOCK_SIZE));
	}
	else
	{
		texture.loadFromFile("../res/sand.png");
		bounds.setTexture(&texture);
	}
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bounds, states);
}

CellCategory Cell::getCategory()
{
	return category;
}

sf::RectangleShape& Cell::getBounds()
{
	return bounds;
}