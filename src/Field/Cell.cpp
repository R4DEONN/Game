#include "Cell.h"
#include "../Common/GameConstants.h"

Cell::Cell(CellCategory Category, sf::Vector2f position, sf::Vector2f size)
{
	category = Category;
	bounds.setPosition(position);
	bounds.setSize(size);
	switch (category)
	{
	case CellCategory::WALL:
		texture.loadFromFile("../res/Tree.png");
		bounds.setTextureRect(sf::IntRect(0, 0, GameConstants::BLOCK_SIZE, GameConstants::BLOCK_SIZE));
		break;
	case CellCategory::SAND:
		texture.loadFromFile("../res/sand.png");
		break;
	case CellCategory::BONES:
		texture.loadFromFile("../res/bones.png");
		break;
	case CellCategory::BLOOD:
		texture.loadFromFile("../res/blood.png");
		break;
	case CellCategory::STONES:
		texture.loadFromFile("../res/stones.png");
		break;
	case CellCategory::GRASS:
		texture.loadFromFile("../res/grass.png");
		break;
	}
	bounds.setTexture(&texture);
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