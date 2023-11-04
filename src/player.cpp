#include "player.h"
#include "field.h"
#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>

Player::Player(const std::string& texturePath, sf::Vector2f position)
	: Entity(texturePath, position)
{
	health = 3;
	speed = 150.f;
	type = EntityType::PLAYER;
	shape.setTextureRect(sf::IntRect(0, 0, 256, 256));
}

void Player::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Entity>>& entities)
{
	updateDirection(
		moveDirection,
		sf::Keyboard::W,
		sf::Keyboard::A,
		sf::Keyboard::S,
		sf::Keyboard::D
	);
	updateDirection(
		attackDirection,
		sf::Keyboard::Up,
		sf::Keyboard::Left,
		sf::Keyboard::Down,
		sf::Keyboard::Right
	);

	auto movement = getMovement(elapsedTime, field);
	//TODO Вынести move в Player
	shape.move(movement);

	if (secondsFromLastShot < 0.75)
	{
		secondsFromLastShot += elapsedTime;
		return;
	}

	if (attackDirection != Direction::NONE)
	{
		secondsFromLastShot = 0;
		const sf::FloatRect playerBounds = shape.getGlobalBounds();
		const sf::Vector2f playerCenter = {
			shape.getPosition().x + playerBounds.width / 2,
			shape.getPosition().y + playerBounds.height / 2,
		};
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(
			"../res/player.png",
			playerCenter,
			attackDirection
			);
		entities.push_back(bullet);
	}
}

void Player::updateDirection(
	Direction& direction,
	sf::Keyboard::Key UpKey,
	sf::Keyboard::Key LeftKey,
	sf::Keyboard::Key DownKey,
	sf::Keyboard::Key RightKey
	)
{
	direction = Direction::NONE;
	if (sf::Keyboard::isKeyPressed(UpKey)
		&& sf::Keyboard::isKeyPressed(DownKey))
	{
		direction = Direction::NONE;
	}
	else if (sf::Keyboard::isKeyPressed(UpKey))
	{
		direction = Direction::UP;
	}
	else if (sf::Keyboard::isKeyPressed(DownKey))
	{
		direction = Direction::DOWN;
	}

	if (sf::Keyboard::isKeyPressed(LeftKey)
		&& sf::Keyboard::isKeyPressed(RightKey))
	{
		switch (direction)
		{
		case Direction::UP_RIGHT:
		case Direction::UP_LEFT:
			direction = Direction::UP;
			break;
		case Direction::DOWN_RIGHT:
		case Direction::DOWN_LEFT:
			direction = Direction::DOWN;
			break;
		default:
			break;
		}
	}
	else if (sf::Keyboard::isKeyPressed(LeftKey))
	{
		switch (direction)
		{
		case Direction::UP:
			direction = Direction::UP_LEFT;
			break;
		case Direction::DOWN:
			direction = Direction::DOWN_LEFT;
			break;
		default:
			direction = Direction::LEFT;
			break;
		}
	}
	else if (sf::Keyboard::isKeyPressed(RightKey))
	{
		switch (direction)
		{
		case Direction::UP:
			direction = Direction::UP_RIGHT;
			break;
		case Direction::DOWN:
			direction = Direction::DOWN_RIGHT;
			break;
		default:
			direction = Direction::RIGHT;
			break;
		}
	}
}
