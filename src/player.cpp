#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

const char PLAYER_TEXTURE[] = "../res/player.png";

constexpr float PLAYER_SPEED = 50.f;

Player::Player()
{
	if (!this->texture.loadFromFile(PLAYER_TEXTURE))
	{
		std::wcerr << L"Не удалось загрузить изображение" << std::endl;
		exit(1);
	}

	const float PLAYER_SIZE = sf::VideoMode::getDesktopMode().height / 16.f;

	this->shape.setSize({
		PLAYER_SIZE,
		PLAYER_SIZE
	});
	this->shape.setPosition(
		sf::VideoMode::getDesktopMode().width / 2,
		sf::VideoMode::getDesktopMode().height / 2
	);;
	this->shape.setTexture(&this->texture);
	this->shape.setOrigin(
		PLAYER_SIZE / 2,
		PLAYER_SIZE / 2
	);
}

void Player::update(float elapsedTime)
{
	const float step = PLAYER_SPEED * elapsedTime;
	sf::Vector2f position = this->shape.getPosition();
	switch (this->moveDirection)
	{
	case Direction::UP:
		position.y -= step;
		break;
	case Direction::UP_LEFT:
		position.x -= step * std::sqrt(2) / 2;
		position.y -= step * std::sqrt(2) / 2;
		break;
	case Direction::UP_RIGHT:
		position.x += step * std::sqrt(2) / 2;
		position.y -= step * std::sqrt(2) / 2;
		break;
	case Direction::DOWN:
		position.y += step;
		break;
	case Direction::DOWN_LEFT:
		position.x -= step * std::sqrt(2) / 2;
		position.y += step * std::sqrt(2) / 2;
		break;
	case Direction::DOWN_RIGHT:
		position.x += step * std::sqrt(2) / 2;
		position.y += step * std::sqrt(2) / 2;
		break;
	case Direction::LEFT:
		position.x -= step;
		break;
	case Direction::RIGHT:
		position.x += step;
		break;
	case Direction::NONE:
		break;
	}

	//TODO implement
	switch (this->attackDirection)
	{
	case Direction::UP:
		break;
	case Direction::UP_LEFT:
		break;
	case Direction::UP_RIGHT:
		break;
	case Direction::DOWN:
		break;
	case Direction::DOWN_LEFT:
		break;
	case Direction::DOWN_RIGHT:
		break;
	case Direction::LEFT:
		break;
	case Direction::RIGHT:
		break;
	case Direction::NONE:
		break;
	}

	this->shape.setPosition(position);
}

void Player::handleKeyPress(const sf::Event::KeyEvent& event)
{
	if (event.code == sf::Keyboard::W)
	{
		if (this->moveDirection == Direction::UP
			|| this->moveDirection == Direction::UP_RIGHT
			|| this->moveDirection == Direction::UP_LEFT)
		{
			return;
		}

		if (this->moveDirection == Direction::LEFT)
		{
			this->moveDirection = Direction::UP_LEFT;
		}
		else if (this->moveDirection == Direction::RIGHT)
		{
			this->moveDirection = Direction::UP_RIGHT;
		}
		else
		{
			this->moveDirection = Direction::UP;
		}
	}
	else if (event.code == sf::Keyboard::S)
	{
		if (this->moveDirection == Direction::DOWN
			|| this->moveDirection == Direction::DOWN_RIGHT
			|| this->moveDirection == Direction::DOWN_LEFT)
		{
			return;
		}

		if (this->moveDirection == Direction::LEFT)
		{
			this->moveDirection = Direction::DOWN_LEFT;
		}
		else if (this->moveDirection == Direction::RIGHT)
		{
			this->moveDirection = Direction::DOWN_RIGHT;
		}
		else
		{
			this->moveDirection = Direction::DOWN;
		}
	}
	else if (event.code == sf::Keyboard::A)
	{
		if (this->moveDirection == Direction::LEFT
			|| this->moveDirection == Direction::UP_LEFT
			|| this->moveDirection == Direction::DOWN_LEFT)
		{
			return;
		}

		if (this->moveDirection == Direction::DOWN)
		{
			this->moveDirection = Direction::DOWN_LEFT;
		}
		else if (this->moveDirection == Direction::UP)
		{
			this->moveDirection = Direction::UP_LEFT;
		}
		else
		{
			this->moveDirection = Direction::LEFT;
		}
	}
	else if (event.code == sf::Keyboard::D)
	{
		if (this->moveDirection == Direction::RIGHT
			|| this->moveDirection == Direction::UP_RIGHT
			|| this->moveDirection == Direction::DOWN_RIGHT)
		{
			return;
		}

		if (this->moveDirection == Direction::DOWN)
		{
			this->moveDirection = Direction::DOWN_RIGHT;
		}
		else if (this->moveDirection == Direction::UP)
		{
			this->moveDirection = Direction::UP_RIGHT;
		}
		else
		{
			this->moveDirection = Direction::RIGHT;
		}
	}
	else if (event.code == sf::Keyboard::Up)
	{
		if (this->attackDirection == Direction::LEFT)
		{
			this->attackDirection = Direction::UP_LEFT;
		}
		else if (this->attackDirection == Direction::RIGHT)
		{
			this->attackDirection = Direction::UP_RIGHT;
		}
		else
		{
			this->attackDirection = Direction::UP;
		}
	}
	else if (event.code == sf::Keyboard::Down)
	{
		if (this->attackDirection == Direction::LEFT)
		{
			this->attackDirection = Direction::DOWN_LEFT;
		}
		else if (this->attackDirection == Direction::RIGHT)
		{
			this->attackDirection = Direction::DOWN_RIGHT;
		}
		else
		{
			this->attackDirection = Direction::DOWN;
		}
	}
	else if (event.code == sf::Keyboard::Left)
	{
		if (this->attackDirection == Direction::DOWN)
		{
			this->attackDirection = Direction::DOWN_LEFT;
		}
		else if (this->attackDirection == Direction::UP)
		{
			this->attackDirection = Direction::UP_LEFT;
		}
		else
		{
			this->attackDirection = Direction::LEFT;
		}
	}
	else if (event.code == sf::Keyboard::Right)
	{
		if (this->attackDirection == Direction::DOWN)
		{
			this->attackDirection = Direction::DOWN_RIGHT;
		}
		else if (this->attackDirection == Direction::UP)
		{
			this->attackDirection = Direction::UP_RIGHT;
		}
		else
		{
			this->attackDirection = Direction::RIGHT;
		}
	}
}

void Player::handleKeyRelease(const sf::Event::KeyEvent& event)
{
	if (event.code == sf::Keyboard::W)
	{
		if (this->moveDirection != Direction::UP
			&& this->moveDirection != Direction::UP_LEFT
			&& this->moveDirection != Direction::UP_RIGHT)
		{
			return;
		}

		if (this->moveDirection == Direction::UP_LEFT)
		{
			this->moveDirection = Direction::LEFT;
		}
		else if (this->moveDirection == Direction::UP_RIGHT)
		{
			this->moveDirection = Direction::RIGHT;
		}
		else
		{
			this->moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::S)
	{
		if (this->moveDirection != Direction::DOWN
			&& this->moveDirection != Direction::DOWN_LEFT
			&& this->moveDirection != Direction::DOWN_RIGHT)
		{
			return;
		}

		if (this->moveDirection == Direction::DOWN_LEFT)
		{
			this->moveDirection = Direction::LEFT;
		}
		else if (this->moveDirection == Direction::DOWN_RIGHT)
		{
			this->moveDirection = Direction::RIGHT;
		}
		else
		{
			this->moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::A)
	{
		if (this->moveDirection != Direction::LEFT
			&& this->moveDirection != Direction::UP_LEFT
			&& this->moveDirection != Direction::DOWN_LEFT)
		{
			return;
		}

		if (this->moveDirection == Direction::DOWN_LEFT)
		{
			this->moveDirection = Direction::DOWN;
		}
		else if (this->moveDirection == Direction::UP_LEFT)
		{
			this->moveDirection = Direction::UP;
		}
		else
		{
			this->moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::D)
	{
		if (this->moveDirection != Direction::RIGHT
			&& this->moveDirection != Direction::UP_RIGHT
			&& this->moveDirection != Direction::DOWN_RIGHT)
		{
			return;
		}

		if (this->moveDirection == Direction::DOWN_RIGHT)
		{
			this->moveDirection = Direction::DOWN;
		}
		else if (this->moveDirection == Direction::UP_RIGHT)
		{
			this->moveDirection = Direction::UP;
		}
		else
		{
			this->moveDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Up)
	{
		if (this->attackDirection == Direction::UP_LEFT)
		{
			this->attackDirection = Direction::LEFT;
		}
		else if (this->attackDirection == Direction::UP_RIGHT)
		{
			this->attackDirection = Direction::RIGHT;
		}
		else
		{
			this->attackDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Down)
	{
		if (this->attackDirection == Direction::DOWN_LEFT)
		{
			this->attackDirection = Direction::LEFT;
		}
		else if (this->attackDirection == Direction::DOWN_RIGHT)
		{
			this->attackDirection = Direction::RIGHT;
		}
		else
		{
			this->attackDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Left)
	{
		if (this->attackDirection == Direction::DOWN_LEFT)
		{
			this->attackDirection = Direction::DOWN;
		}
		else if (this->attackDirection == Direction::UP_LEFT)
		{
			this->attackDirection = Direction::UP;
		}
		else
		{
			this->attackDirection = Direction::NONE;
		}
	}
	else if (event.code == sf::Keyboard::Right)
	{
		if (this->attackDirection == Direction::DOWN_RIGHT)
		{
			this->attackDirection = Direction::DOWN;
		}
		else if (this->attackDirection == Direction::UP_RIGHT)
		{
			this->attackDirection = Direction::UP;
		}
		else
		{
			this->attackDirection = Direction::NONE;
		}
	}
}

sf::RectangleShape Player::getShape()
{
	return this->shape;
}