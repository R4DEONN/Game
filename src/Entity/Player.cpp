#include "Player.h"
#include "Bullet.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "../Common/GameConstants.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Utils.h"
#include <iostream>
#include <cmath>
#include <memory>

const float BODY_SIZE = BLOCK_SIZE * 39 / 48;
const float FOOT_SIZE = BLOCK_SIZE * 9 / 48;

Player::Player(const std::string& bodyTexturePath, const std::string& footTexturePath, sf::Vector2f position)
	: Entity(bodyTexturePath, position)
{
	if (!footTexture.loadFromFile(footTexturePath))
	{
		//TODO Нормальео обрабатывать ошибку
		std::wcerr << L"Не удалось загрузить изображение" << std::endl;
		exit(1);
	}

	shape.setSize({
		BLOCK_SIZE,
		BODY_SIZE,
	});
	foot.setSize({
        BLOCK_SIZE * 32 / 48,
		FOOT_SIZE
	});
	foot.setTexture(&footTexture);
	foot.setTextureRect(sf::IntRect(0, 10, 32, 9));
	foot.setPosition(shape.getPosition().x - 26, shape.getPosition().y + 19);
	shape.setTextureRect(sf::IntRect(48 * 2, 0, 48, 39));

	shootBuffer.loadFromFile("../res/bullet_sound.ogg");
	shoot.setBuffer(shootBuffer);
	health = 3;
	speed = 220.f;
	type = EntityType::PLAYER;
}

void Player::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets)
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
	foot.move(movement);

	if (movement.x != 0 || movement.y != 0)
	{
		moveTimer += elapsedTime;
		const char maxImages = 4;
		const float frameDuration = 0.1;
		const char frameSize = 32;
		const int curPixel = (int(moveTimer / frameDuration) % maxImages) * FOOT_SIZE;
		foot.setTextureRect(sf::IntRect(0, curPixel, frameSize, 9));
		if (moveTimer > maxImages * frameDuration)
		{
			moveTimer = 0;
		}

		if (movement.y < 0
			&& attackDirection != Direction::DOWN
			&& attackDirection != Direction::DOWN_RIGHT
			&& attackDirection != Direction::DOWN_LEFT)
		{
			shape.setTextureRect(sf::IntRect(0, 0, 48, 39));
		}
		else
		{
			shape.setTextureRect(sf::IntRect(48 * 2, 0, 48, 39));
		}
	}
	else
	{
		moveTimer = 0;
		foot.setTextureRect(sf::IntRect(0, 9, 32, 9));
		shape.setTextureRect(sf::IntRect(48 * 2, 0, 48, 39));
	}


	if (secondsFromLastShot < 0.3)
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
			"../res/Bullet.png",
			playerCenter,
			attackDirection
			);
		bullets.push_back(bullet);
		shoot.play();
	}
}

void Player::movePlayerToCenter()
{
	const sf::Vector2f position = getCenterCoordinates();
	const sf::Vector2f delta = {-26, 19};
	shape.setPosition(position);
	foot.setPosition(position + delta);
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

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(foot, states);
	target.draw(shape, states);
}
