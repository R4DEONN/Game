#include "cell.h"

Cell::Cell(CellCategory category, sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	this->category = category;
	this->bounds.setPosition(position);
	this->bounds.setSize(size);
	this->bounds.setFillColor(color);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->bounds, states);
}

CellCategory Cell::getCategory() const
{
	return this->category;
}

sf::RectangleShape Cell::getBounds() const
{
	return this->bounds;
}