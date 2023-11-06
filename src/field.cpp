#include <iostream>
#include <memory>
#include "field.h"
#include "cell.h"
#include "gameConstants.h"
#include "utils.h"

const float BLOCK_SIZE = GameConstants::BLOCK_SIZE;
const float CENTER_OFFSET_X = GameConstants::CENTER_OFFSET_X;
const float CENTER_OFFSET_Y = GameConstants::CENTER_OFFSET_Y;

//TODO Сделать проходы по 3 ячейки
static const char FIELD_MAZE[] = {
	1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
};

static const sf::Color WALL_COLOR = sf::Color(163, 58, 3);
static const sf::Color PRAIRIE_COLOR = sf::Color(50, 168, 82);

Field::Field()
{
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			const size_t offset = x + y * width;
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
			std::shared_ptr<Cell> cell = std::make_shared<Cell>(
				category,
				position,
				size,
				color
			);
			cells.push_back(cell);
		}
	}
}

sf::Vector2f Field::checkFieldWallsCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement)
{
	sf::Vector2f newMovement = checkFieldGameCollision(oldBounds, movement);
	if (newMovement == sf::Vector2f{ 0, 0 })
	{
		return newMovement;
	}

	sf::FloatRect newBounds = moveRect(oldBounds, newMovement);
	for (size_t i = 0, n = width * height; i < n; i++)
	{
		Cell& cell = *cells[i];
		if (cell.getCategory() == CellCategory::PRAIRIE)
		{
			continue;
		}

		sf::FloatRect cellBound = cell.getBounds().getGlobalBounds();
		if (newBounds.intersects(cellBound))
		{
			//TODO Вынести в булевы переменные
			if ((cellBound.top == CENTER_OFFSET_Y
				 || (cellBound.top + cellBound.height == (height / 2 - 1) * BLOCK_SIZE + CENTER_OFFSET_Y
					 && (oldBounds.left<BLOCK_SIZE + CENTER_OFFSET_X
										|| oldBounds.left + oldBounds.width>(width - 1) * BLOCK_SIZE
						 + CENTER_OFFSET_X)))
				&& oldBounds.top >= BLOCK_SIZE + CENTER_OFFSET_Y
				&& newMovement.y < 0)
			{
				newMovement.y = cellBound.top + cellBound.height - oldBounds.top;
			}

			if ((cellBound.top + cellBound.height == height * BLOCK_SIZE + CENTER_OFFSET_Y
				 || (cellBound.top == (height / 2 + 2) * BLOCK_SIZE + CENTER_OFFSET_Y
					 && (oldBounds.left<BLOCK_SIZE + CENTER_OFFSET_X
										|| oldBounds.left + oldBounds.width>(width - 1) * BLOCK_SIZE
						 + CENTER_OFFSET_X)))
				&& oldBounds.top + oldBounds.height <= (height - 1) * BLOCK_SIZE + CENTER_OFFSET_Y
				&& newMovement.y > 0)
			{
				newMovement.y = cellBound.top - oldBounds.height - oldBounds.top;
			}

			if ((cellBound.left == CENTER_OFFSET_X
				 || (cellBound.left + cellBound.width == (width / 2 - 1) * BLOCK_SIZE + CENTER_OFFSET_X
					 && (oldBounds.top<BLOCK_SIZE + CENTER_OFFSET_Y
									   || oldBounds.top + oldBounds.height>(height - 1) * BLOCK_SIZE  + CENTER_OFFSET_Y)))
				&& oldBounds.left >= BLOCK_SIZE + CENTER_OFFSET_X
				&& newMovement.x < 0)
			{
				newMovement.x = cellBound.left + cellBound.width - oldBounds.left;
			}

			if ((cellBound.left + cellBound.width == width * BLOCK_SIZE + CENTER_OFFSET_X
				 || (cellBound.left == (width / 2 + 2) * BLOCK_SIZE + CENTER_OFFSET_X
					 && (oldBounds.top<BLOCK_SIZE + CENTER_OFFSET_Y
									   || oldBounds.top + oldBounds.height>(height - 1) * BLOCK_SIZE + CENTER_OFFSET_Y)))
				&& oldBounds.left + oldBounds.width <= (width - 1) * BLOCK_SIZE + CENTER_OFFSET_X
				&& newMovement.x > 0)
			{
				newMovement.x = cellBound.left - oldBounds.width - oldBounds.left;
			}

			newBounds = moveRect(oldBounds, newMovement);
		}
	}
	return newMovement;
}

sf::Vector2f Field::checkFieldGameCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement)
{
	sf::FloatRect newBounds = moveRect(oldBounds, movement);
	sf::Vector2f newMovement = movement;
	//TODO Вынести в булевы переменные
	if (newBounds.top < CENTER_OFFSET_Y
		&& movement.y < 0)
	{
		newMovement.y = 0 - oldBounds.top + CENTER_OFFSET_Y;
	}
	if (newBounds.top + newBounds.height > height * BLOCK_SIZE + CENTER_OFFSET_Y
		&& movement.y > 0)
	{
		newMovement.y = height * BLOCK_SIZE - (oldBounds.top + oldBounds.height) + CENTER_OFFSET_Y;
	}
	if (newBounds.left < CENTER_OFFSET_X
		&& movement.x < 0)
	{
		newMovement.x = 0 - oldBounds.left + CENTER_OFFSET_X;
	}
	if (newBounds.left + newBounds.width > width * BLOCK_SIZE + CENTER_OFFSET_X
		&& movement.x > 0)
	{
		newMovement.x = width * BLOCK_SIZE + CENTER_OFFSET_X - (oldBounds.left + oldBounds.width);
	}

	return newMovement;
}

void Field::update(float elapsedTime)
{
	moveTimer += elapsedTime;
	for (const auto& cell : cells)
	{
		if (cell->getCategory() == CellCategory::WALL)
		{
			const char maxImages = 2;
			const float frameDuration = 1;
			const char frameSize = GameConstants::BLOCK_SIZE;
			const int curPixel = (int(moveTimer / frameDuration) % maxImages) * frameSize;
			cell->getBounds().setTextureRect(sf::IntRect(curPixel, 0, frameSize, frameSize));
			if (moveTimer > 2 * frameDuration)
			{
				moveTimer = 0;
			}
		}
	}
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < width * height; i++)
	{
		target.draw(*cells[i], states);
	}
}
