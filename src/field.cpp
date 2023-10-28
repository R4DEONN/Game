#include <iostream>
#include "field.h"
#include "cell.h"

static const float BLOCK_SIZE = sf::VideoMode::getDesktopMode().height / 16;
static const float CENTER_OFFSET =
	(sf::VideoMode::getDesktopMode().width - sf::VideoMode::getDesktopMode().height) / 2;
static const size_t FIELD_WIDTH = 16;
static const size_t FIELD_HEIGHT = 16;
static const char FIELD_MAZE[] = {
	1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
};

static const sf::Color WALL_COLOR = sf::Color(163, 58, 3);
static const sf::Color PRAIRIE_COLOR = sf::Color(50, 168, 82);

Field::Field()
{
	this->width = FIELD_WIDTH;
	this->height = FIELD_HEIGHT;
	for (size_t y = 0; y < this->height; y++)
	{
		for (size_t x = 0; x < this->width; x++)
		{
			const size_t offset = x + y * this->width;
			CellCategory category;
			sf::Color color;
			if (FIELD_MAZE[offset] == 1)
			{
				category = CellCategory::WALL;
				color = WALL_COLOR;
			}
			else
			{
				category = CellCategory::PRAIRIE;
				color = PRAIRIE_COLOR;
			}
			const sf::Vector2f position = {
				x * BLOCK_SIZE + CENTER_OFFSET,
				y * BLOCK_SIZE
			};
			const sf::Vector2f size = { BLOCK_SIZE, BLOCK_SIZE };
			Cell cell(
				category,
				position,
				size,
				color
			);
			this->cells.push_back(cell);
		}
	}
}

static sf::FloatRect moveRect(const sf::FloatRect& rect, sf::Vector2f& offset)
{
	return { rect.left + offset.x, rect.top + offset.y, rect.width, rect.height };
}

sf::Vector2f Field::getPlayerStartPosition()
{
	sf::Vector2f position(
		sf::VideoMode::getDesktopMode().width / 2,
		sf::VideoMode::getDesktopMode().height / 2
	);
	return position;
}

sf::Vector2f Field::checkFieldWallsCollision(const sf::FloatRect& oldBounds, sf::Vector2f& movement)
{
	sf::FloatRect newBounds = moveRect(oldBounds, movement);
	for (size_t i = 0, n = this->width * this->height; i < n; i++)
	{
		const Cell& cell = this->cells[i];
		if (cell.getCategory() == CellCategory::PRAIRIE)
		{
			continue;
		}

		sf::FloatRect cellBound = cell.getBounds().getGlobalBounds();
		if (newBounds.intersects(cellBound))
		{
			//TODO Вынести в булевы переменные
			if ((cellBound.top == 0
				|| (cellBound.top + cellBound.height == (this->height / 2 - 1) * BLOCK_SIZE
				&& (oldBounds.left < BLOCK_SIZE + CENTER_OFFSET
				|| oldBounds.left + oldBounds.width > (this->width - 1) * BLOCK_SIZE + CENTER_OFFSET)))
				&& oldBounds.top > BLOCK_SIZE
				&& movement.y < 0)
			{
				movement.y = cellBound.top + cellBound.height - oldBounds.top;
			}
			if ((cellBound.top + cellBound.height == this->height * BLOCK_SIZE
				|| (cellBound.top == (this->height / 2 + 1) * BLOCK_SIZE
				&& (oldBounds.left < BLOCK_SIZE + CENTER_OFFSET
				|| oldBounds.left + oldBounds.width > (this->width - 1) * BLOCK_SIZE + CENTER_OFFSET)))
				&& oldBounds.top + oldBounds.height < this->height * BLOCK_SIZE
				&& movement.y > 0)
			{
				movement.y = cellBound.top - oldBounds.height - oldBounds.top;
			}
			if ((cellBound.left == CENTER_OFFSET
				|| (cellBound.left + cellBound.width == (this->width / 2 - 1) * BLOCK_SIZE + CENTER_OFFSET
				&& (oldBounds.top < BLOCK_SIZE
				|| oldBounds.top + oldBounds.height > (this->height - 1) * BLOCK_SIZE)))
				&& oldBounds.left > CENTER_OFFSET
				&& movement.x < 0)
			{
				movement.x = cellBound.left + cellBound.width - oldBounds.left;
			}
			if ((cellBound.left + cellBound.width == this->width * BLOCK_SIZE + CENTER_OFFSET
				|| (cellBound.left == (this->width / 2 + 1) * BLOCK_SIZE + CENTER_OFFSET
				&& (oldBounds.top < BLOCK_SIZE
				|| oldBounds.top + oldBounds.height > (this->height - 1) * BLOCK_SIZE)))
				&& oldBounds.left + oldBounds.width < this->width * BLOCK_SIZE + CENTER_OFFSET
				&& movement.x > 0)
			{
				movement.x = cellBound.left - oldBounds.width - oldBounds.left;
			}

			newBounds = moveRect(oldBounds, movement);
		}
	}
	return movement;
}

void Field::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < this->width * this->height; i++)
	{
		window.draw(this->cells[i]);
	}
}