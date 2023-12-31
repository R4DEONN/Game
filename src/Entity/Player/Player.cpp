#include "Player.h"
#include "../Bullet.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "../../Common/GameConstants.h"
#include "SFML/Graphics.hpp"
#include "../../Utils/Utils.h"
#include <iostream>
#include <cmath>
#include <memory>

const float BODY_SIZE = BLOCK_SIZE * 39 / 48;
const float FOOT_SIZE = BLOCK_SIZE * 9 / 48;

const std::string BODY_TEXTURE_PATH = "../res/body.png";
const std::string FOOT_TEXTURE_PATH = "../res/foot.png";

Player::Player(int playerHealth, sf::Vector2f position)
: entity(BODY_TEXTURE_PATH, position)
{
	if (!footTexture.loadFromFile(FOOT_TEXTURE_PATH))
	{
		throw "Wrong file name";
	}

	entity.shape.setSize({
		BLOCK_SIZE,
		BODY_SIZE,
	});
	foot.setSize({
        BLOCK_SIZE * 32 / 48,
		FOOT_SIZE
	});
	foot.setTexture(&footTexture);
	foot.setTextureRect(sf::IntRect(0, 9, 32, 9));
	foot.setPosition(entity.shape.getPosition().x - 26, entity.shape.getPosition().y + 19);
	entity.shape.setTextureRect(sf::IntRect(48 * 2, 0, 48, 39));

	shootBuffer.loadFromFile("../res/bullet_sound.ogg");
	shootSound.setBuffer(shootBuffer);
	entity.setHealth(playerHealth);
	entity.setSpeed(BLOCK_SIZE * 4.5);
	entity.setType(EntityType::PLAYER);
}

void Player::setSpeed(float newSpeed)
{
	entity.setSpeed(newSpeed);
}

void Player::update(float elapsedTime, Field& field, std::vector<std::shared_ptr<Bullet>>& bullets)
{
	updateDirection(entity.getMoveDirection(), sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D);
	updateDirection(attackDirection, sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Right);

	auto movement = entity.getMovement(elapsedTime, field);
	move(movement);

	if (movement.x != 0 || movement.y != 0)
	{
		entity.setMoveTimer(entity.getMoveTimer() + elapsedTime);
		const char maxImages = 4;
		const float frameDuration = 0.15;
		const char frameSize = 32;
		const int curPixel = (int(entity.getMoveTimer() / frameDuration) % maxImages) * 9;
		foot.setTextureRect(sf::IntRect(0, curPixel, frameSize, 9));
		if (entity.getMoveTimer() > maxImages * frameDuration)
		{
			entity.setMoveTimer(0);
		}

		if (movement.y < 0
			&& attackDirection != Direction::DOWN
			&& attackDirection != Direction::DOWN_RIGHT
			&& attackDirection != Direction::DOWN_LEFT)
		{
			entity.shape.setTextureRect(sf::IntRect(0, 0, 48, 39));
		}
		else
		{
			entity.shape.setTextureRect(sf::IntRect(48 * 2, 0, 48, 39));
		}
	}
	else
	{
		entity.setMoveTimer(0);
		foot.setTextureRect(sf::IntRect(0, 9, 32, 9));
		entity.shape.setTextureRect(sf::IntRect(48 * 2, 0, 48, 39));
	}

	if (secondsFromLastShot < delayToShot)
	{
		secondsFromLastShot += elapsedTime;
		return;
	}

	if (attackDirection != Direction::NONE)
	{
		secondsFromLastShot = 0;
		shoot(bullets);
		shootSound.play();
	}
}

void makeBullet(sf::Vector2f playerCenter, Direction direction, std::vector<std::shared_ptr<Bullet>>& bullets)
{
	auto bullet = std::make_shared<Bullet>(
		"../res/Bullet.png",
		playerCenter,
		direction
	);

	bullets.push_back(bullet);
}

void Player::shoot(std::vector<std::shared_ptr<Bullet>>& bullets)
{
	const sf::FloatRect playerBounds = entity.getShape().getGlobalBounds();
	const sf::Vector2f playerCenter = {
		entity.getShape().getPosition().x + playerBounds.width / 2,
		entity.getShape().getPosition().y + playerBounds.height / 2,
	};
	if (shootingType == ShootingType::SINGLE)
	{
		makeBullet(playerCenter, attackDirection, bullets);
		return;
	}
	else if (shootingType == ShootingType::EIGHT)
	{
		makeBullet(playerCenter, Direction::UP, bullets);
		makeBullet(playerCenter, Direction::UP_RIGHT, bullets);
		makeBullet(playerCenter, Direction::RIGHT, bullets);
		makeBullet(playerCenter, Direction::DOWN_RIGHT, bullets);
		makeBullet(playerCenter, Direction::DOWN, bullets);
		makeBullet(playerCenter, Direction::DOWN_LEFT, bullets);
		makeBullet(playerCenter, Direction::LEFT, bullets);
		makeBullet(playerCenter, Direction::UP_LEFT, bullets);
		return;
	}

	Direction firstBulletDirection = int(attackDirection) - 1 == 0 ? Direction(16) : Direction(int(attackDirection) - 1);

	Direction thirdBulletDirection = int(attackDirection) + 1 == 17 ? Direction(1) : Direction(int(attackDirection) + 1);

	makeBullet(playerCenter, firstBulletDirection, bullets);
	makeBullet(playerCenter, attackDirection, bullets);
	makeBullet(playerCenter, thirdBulletDirection, bullets);
}

void Player::move(const sf::Vector2f movement)
{
	entity.shape.move(movement);
	foot.move(movement);
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
	target.draw(entity.getShape(), states);
	if (item)
	{
		target.draw(item->getImmutableShape(), states);
	}
}

sf::RectangleShape Player::getShape() const
{
	return entity.getShape();
}

int Player::getHealth()
{
	return entity.getHealth();
}

sf::Vector2f Player::getPosition()
{
	return entity.getPosition();
}

Direction& Player::getMoveDirection()
{
	return entity.getMoveDirection();
}

float Player::getMoveTimer()
{
	return entity.getMoveTimer();
}

void Player::setMoveTimer(float newTime)
{
	entity.setMoveTimer(newTime);
}

void Player::setHealth(int newHealth)
{
	entity.setHealth(newHealth);
}

void Player::setItem(std::shared_ptr<IItem> newItem)
{
	item = newItem;
	item->setPosition({
		CENTER_OFFSET_X - float(BLOCK_SIZE * 1.375) / 2 - 15,
		CENTER_OFFSET_Y + float(BLOCK_SIZE * 1.375) / 2
	});
}

std::shared_ptr<IItem> Player::getItem()
{
	return item;
}

void Player::setDelayToShot(float newDelay)
{
	delayToShot = newDelay;
}

void Player::setShootingType(ShootingType type)
{
	shootingType = type;
}

EntityType Player::getType()
{
	return entity.getType();
}

float Player::getDelayToShot()
{
	return delayToShot;
}

float Player::getSpeed()
{
	return entity.getSpeed();
}
