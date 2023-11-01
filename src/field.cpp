#include <iostream>
#include "field.h"
#include "cell.h"
#include "gameConstants.h"

const float BLOCK_SIZE = GameConstants::BLOCK_SIZE;
const float CENTER_OFFSET_X = GameConstants::CENTER_OFFSET_X;
const float CENTER_OFFSET_Y = GameConstants::CENTER_OFFSET_Y;

//TODO Сделать проходы по 3 ячейки
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
				x * BLOCK_SIZE + CENTER_OFFSET_X,
				y * BLOCK_SIZE + CENTER_OFFSET_Y
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
	this->checkFieldGameCollision(oldBounds, movement);
	if (movement == sf::Vector2f{ 0, 0 })
	{
		return movement;
	}

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
			if ((cellBound.top == CENTER_OFFSET_Y
				 || (cellBound.top + cellBound.height == (this->height / 2 - 1) * BLOCK_SIZE + CENTER_OFFSET_Y
					 && (oldBounds.left<BLOCK_SIZE + CENTER_OFFSET_X
										|| oldBounds.left + oldBounds.width>(this->width - 1) * BLOCK_SIZE
						 + CENTER_OFFSET_X)))
				&& oldBounds.top >= BLOCK_SIZE + CENTER_OFFSET_Y
				&& movement.y < 0)
			{
				movement.y = cellBound.top + cellBound.height - oldBounds.top;
			}

			if ((cellBound.top + cellBound.height == this->height * BLOCK_SIZE + CENTER_OFFSET_Y
				 || (cellBound.top == (this->height / 2 + 1) * BLOCK_SIZE + CENTER_OFFSET_Y
					 && (oldBounds.left<BLOCK_SIZE + CENTER_OFFSET_X
										|| oldBounds.left + oldBounds.width>(this->width - 1) * BLOCK_SIZE
						 + CENTER_OFFSET_X)))
				&& oldBounds.top + oldBounds.height <= (this->height - 1) * BLOCK_SIZE + CENTER_OFFSET_Y
				&& movement.y > 0)
			{
				movement.y = cellBound.top - oldBounds.height - oldBounds.top;
			}

			if ((cellBound.left == CENTER_OFFSET_X
				 || (cellBound.left + cellBound.width == (this->width / 2 - 1) * BLOCK_SIZE + CENTER_OFFSET_X
					 && (oldBounds.top<BLOCK_SIZE + CENTER_OFFSET_Y
									   || oldBounds.top + oldBounds.height>(this->height - 1) * BLOCK_SIZE  + CENTER_OFFSET_Y)))
				&& oldBounds.left >= BLOCK_SIZE + CENTER_OFFSET_X
				&& movement.x < 0)
			{
				movement.x = cellBound.left + cellBound.width - oldBounds.left;
			}

			if ((cellBound.left + cellBound.width == this->width * BLOCK_SIZE + CENTER_OFFSET_X
				 || (cellBound.left == (this->width / 2 + 1) * BLOCK_SIZE + CENTER_OFFSET_X
					 && (oldBounds.top<BLOCK_SIZE + CENTER_OFFSET_Y
									   || oldBounds.top + oldBounds.height>(this->height - 1) * BLOCK_SIZE + CENTER_OFFSET_Y)))
				&& oldBounds.left + oldBounds.width <= (this->width - 1) * BLOCK_SIZE + CENTER_OFFSET_X
				&& movement.x > 0)
			{
				movement.x = cellBound.left - oldBounds.width - oldBounds.left;
			}

			newBounds = moveRect(oldBounds, movement);
		}
	}
	return movement;
}

sf::Vector2f Field::checkFieldGameCollision(const sf::FloatRect& oldBounds, sf::Vector2f& movement)
{
	sf::FloatRect newBounds = moveRect(oldBounds, movement);
	//TODO Вынести в булевы переменные
	if (newBounds.top < CENTER_OFFSET_Y
		&& movement.y < 0)
	{
		movement.y = 0 - oldBounds.top + CENTER_OFFSET_Y;
	}
	if (newBounds.top + newBounds.height > this->height * BLOCK_SIZE + CENTER_OFFSET_Y
		&& movement.y > 0)
	{
		movement.y = this->height * BLOCK_SIZE - (oldBounds.top + oldBounds.height) + CENTER_OFFSET_Y;
	}
	if (newBounds.left < CENTER_OFFSET_X
		&& movement.x < 0)
	{
		movement.x = 0 - oldBounds.left + CENTER_OFFSET_X;
	}
	if (newBounds.left + newBounds.width > this->width * BLOCK_SIZE + CENTER_OFFSET_X
		&& movement.x > 0)
	{
		movement.x = this->width * BLOCK_SIZE + CENTER_OFFSET_X - (oldBounds.left + oldBounds.width);
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