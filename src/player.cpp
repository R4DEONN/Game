#include "player.h"
#include "field.h"
#include "gameConstants.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

Player::Player(const std::string& texturePath, sf::Vector2f position)
	: Entity(texturePath, position)
{
	health = 3;
	speed = 250.f;
}

void Player::update(float elapsedTime, Field& field, std::vector<Entity*>& entities)
{
	const float step = speed * elapsedTime;
	sf::Vector2f movement(0.f, 0.f);
	switch (moveDirection)
	{
	case Direction::UP:
		movement.y -= step;
		break;
	case Direction::UP_LEFT:
		movement.x -= step * std::sqrt(2) / 2;
		movement.y -= step * std::sqrt(2) / 2;
		break;
	case Direction::UP_RIGHT:
		movement.x += step * std::sqrt(2) / 2;
		movement.y -= step * std::sqrt(2) / 2;
		break;
	case Direction::DOWN:
		movement.y += step;
		break;
	case Direction::DOWN_LEFT:
		movement.x -= step * std::sqrt(2) / 2;
		movement.y += step * std::sqrt(2) / 2;
		break;
	case Direction::DOWN_RIGHT:
		movement.x += step * std::sqrt(2) / 2;
		movement.y += step * std::sqrt(2) / 2;
		break;
	case Direction::LEFT:
		movement.x -= step;
		break;
	case Direction::RIGHT:
		movement.x += step;
		break;
	case Direction::NONE:
		break;
	}

	const sf::FloatRect playerBounds = shape.getGlobalBounds();
	movement = field.checkFieldWallsCollision(playerBounds, movement);
	//TODO Вынести move в Player
	shape.move(movement);

	if (secondsFromLastShot < 0.25f)
	{
		secondsFromLastShot += elapsedTime;
		return;
	}

	secondsFromLastShot = 0;
	const sf::Vector2f playerCenter = {
		shape.getPosition().x + playerBounds.width / 2,
		shape.getPosition().y + playerBounds.height / 2,
	};
	if (attackDirection != Direction::NONE)
	{
		Bullet* bullet = new Bullet{
			"../res/player.png",
			playerCenter,
			attackDirection
		};
		entities.push_back(bullet);
	}
}

void Player::handleKeyPress(const sf::Event::KeyEvent& event)
{
	if (event.code == sf::Keyboard::W)
	{
		if (moveDirection == Direction::UP
			|| moveDirection == Direction::UP_RIGHT
			|| moveDirection == Direction::UP_LEFT)
		{
			return;
		}

		if (moveDirection == Direction::LEFT)
		{
			moveDirection = Direction::UP_LEFT;
		}
		else if (moveDirection == Direction::RIGHT)
		{
			moveDirection = Direction::UP_RIGHT;
		}
		else
		{
			moveDirection = Direction::UP;
		}
	}
	else if (event.code == sf::Keyboard::S)
	{
		if (moveDirection == Direction::DOWN
			|| moveDirection == Direction::DOWN_RIGHT
			|| moveDirection == Direction::DOWN_LEFT)
		{
			return;
		}

		if (moveDirection == Direction::LEFT)
		{
			moveDirection = Direction::DOWN_LEFT;
		}
		else if (moveDirection == Direction::RIGHT)
		{
			moveDirection = Direction::DOWN_RIGHT;
		}
		else
		{
			moveDirection = Direction::DOWN;
		}
	}
	else if (event.code == sf::Keyboard::A)
	{
		if (moveDirection == Direction::LEFT
			|| moveDirection == Direction::UP_LEFT
			|| moveDirection == Direction::DOWN_LEFT)
		{
			return;
		}

		if (moveDirection == Direction::DOWN)
		{
			moveDirection = Direction::DOWN_LEFT;
		}
		else if (moveDirection == Direction::UP)
		{
			moveDirection = Direction::UP_LEFT;
		}
		else
		{
			moveDirection = Direction::LEFT;
		}
	}
	else if (event.code == sf::Keyboard::D)
	{
		if (moveDirection == Direction::RIGHT
			|| moveDirection == Direction::UP_RIGHT
			|| moveDirection == Direction::DOWN_RIGHT)
		{
			return;
		}

		if (moveDirection == Direction::DOWN)
		{
			moveDirection = Direction::DOWN_RIGHT;
		}
		else if (moveDirection == Direction::UP)
		{
			moveDirection = Direction::UP_RIGHT;
		}
		else
		{
			moveDirection = Direction::RIGHT;
		}
	}
	else if (event.code == sf::Keyboard::Up)
	{
		if (attackDirection == Direction::LEFT)
		{
			attackDirection = Direction::UP_LEFT;
		}
		else if (attackDirection == Direction::RIGHT)
		{
			attackDirection = Direction::UP_RIGHT;
		}
		else
		{
			attackDirection = Direction::UP;
		}
	}
	else if (event.code == sf::Keyboard::Down)
	{
		if (attackDirection == Direction::LEFT)
		{
			attackDirection = Direction::DOWN_LEFT;
		}
		else if (attackDirection == Direction::RIGHT)
		{
			attackDirection = Direction::DOWN_RIGHT;
		}
		else
		{
			attackDirection = Direction::DOWN;
		}
	}
	else if (event.code == sf::Keyboard::Left)
	{
		if (attackDirection == Direction::DOWN)
		{
			attackDirection = Direction::DOWN_LEFT;
		}
		else if (attackDirection == Direction::UP)
		{
			attackDirection = Direction::UP_LEFT;
		}
		else
		{
			attackDirection = Direction::LEFT;
		}
	}
	else if (event.code == sf::Keyboard::Right)
	{
		if (attackDirection == Direction::DOWN)
		{
			attackDirection = Direction::DOWN_RIGHT;
		}
		else if (attackDirection == Direction::UP)
		{
			attackDirection = Direction::UP_RIGHT;
		}
		else
		{
			attackDirection = Direction::RIGHT;
		}
	}
}

void Player::handleKeyRelease(const sf::Event::KeyEvent& event)
{
	if (event.code == sf::Keyboard::W)
	{
		if (moveDirection != Direction::UP
			&& moveDirection != Direction::UP_LEFT
			&& moveDirection != Direction::UP_RIGHT)
		{
			return;
		}

		if (moveDirection == Direction::UP_LEFT)
		{
			moveDirection = Direction::LEFT;
		}
		else if (moveDirection == Direction::UP_RIGHT)
		{
			moveDirection = Direction::RIGHT;
		}
		else
		{
			moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::S)
	{
		if (moveDirection != Direction::DOWN
			&& moveDirection != Direction::DOWN_LEFT
			&& moveDirection != Direction::DOWN_RIGHT)
		{
			return;
		}

		if (moveDirection == Direction::DOWN_LEFT)
		{
			moveDirection = Direction::LEFT;
		}
		else if (moveDirection == Direction::DOWN_RIGHT)
		{
			moveDirection = Direction::RIGHT;
		}
		else
		{
			moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::A)
	{
		if (moveDirection != Direction::LEFT
			&& moveDirection != Direction::UP_LEFT
			&& moveDirection != Direction::DOWN_LEFT)
		{
			return;
		}

		if (moveDirection == Direction::DOWN_LEFT)
		{
			moveDirection = Direction::DOWN;
		}
		else if (moveDirection == Direction::UP_LEFT)
		{
			moveDirection = Direction::UP;
		}
		else
		{
			moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::D)
	{
		if (moveDirection != Direction::RIGHT
			&& moveDirection != Direction::UP_RIGHT
			&& moveDirection != Direction::DOWN_RIGHT)
		{
			return;
		}

		if (moveDirection == Direction::DOWN_RIGHT)
		{
			moveDirection = Direction::DOWN;
		}
		else if (moveDirection == Direction::UP_RIGHT)
		{
			moveDirection = Direction::UP;
		}
		else
		{
			moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Up)
	{
		if (attackDirection == Direction::UP_LEFT)
		{
			attackDirection = Direction::LEFT;
		}
		else if (attackDirection == Direction::UP_RIGHT)
		{
			attackDirection = Direction::RIGHT;
		}
		else
		{
			attackDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Down)
	{
		if (attackDirection == Direction::DOWN_LEFT)
		{
			attackDirection = Direction::LEFT;
		}
		else if (attackDirection == Direction::DOWN_RIGHT)
		{
			attackDirection = Direction::RIGHT;
		}
		else
		{
			attackDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Left)
	{
		if (attackDirection == Direction::DOWN_LEFT)
		{
			attackDirection = Direction::DOWN;
		}
		else if (attackDirection == Direction::UP_LEFT)
		{
			attackDirection = Direction::UP;
		}
		else
		{
			attackDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Right)
	{
		if (attackDirection == Direction::DOWN_RIGHT)
		{
			attackDirection = Direction::DOWN;
		}
		else if (attackDirection == Direction::UP_RIGHT)
		{
			attackDirection = Direction::UP;
		}
		else
		{
			attackDirection = Direction::NONE;
		}
	}
}
