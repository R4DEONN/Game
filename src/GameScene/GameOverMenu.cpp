//
// Created by admin on 15.11.2023.
//

#include "GameOverMenu.h"
#include "../Common/GameConstants.h"

GameOverMenu::GameOverMenu()
{
	triangle.setOutlineColor(sf::Color::White);
	triangle.setOutlineThickness(2);
	triangle.setFillColor(sf::Color::Black);
	triangle.setPointCount(3);
	triangle.setPoint(0, {0, -8});
	triangle.setPoint(1, {0, 8});
	triangle.setPoint(2, {15, 0});

	font.loadFromFile("../res/Minecraft Rus NEW.otf");

	endGame.setFont(font);
	endGame.setStyle(sf::Text::Bold);
	endGame.setFillColor(sf::Color::White);
	endGame.setCharacterSize(BLOCK_SIZE / 3);
	endGame.setString(L"Конец игры");
	endGame.setPosition({
			0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
			0.45f * sf::VideoMode::getDesktopMode().height,
	});

	again.setFont(font);
	again.setFillColor(sf::Color::White);
	again.setCharacterSize(BLOCK_SIZE / 3);
	again.setString(L"Заново");
	again.setPosition({
			0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2 + triangle.getLocalBounds().width + 10,
			0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2),
	});

	exit.setFont(font);
	exit.setFillColor(sf::Color::White);
	exit.setCharacterSize(BLOCK_SIZE / 3);
	exit.setString(L"Выход");
	exit.setPosition({
			0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
			0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 3 + 20,
	});

	triangle.setPosition({
			0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
			0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6,
	});
}

int GameOverMenu::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		triangle.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6 + BLOCK_SIZE / 3 + 20,
		});
		exit.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2 + triangle.getLocalBounds().width + 10,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 3 + 20,
		});

		again.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2),
		});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		triangle.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6,
		});
		exit.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 3 + 20,
		});

		again.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2 + triangle.getLocalBounds().width + 10,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2),
		});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		const float triangleY = triangle.getPosition().y;
		triangle.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - endGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6,
		});
		if (triangleY == 0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6)
		{
			return 1;
		}
		return 0;
	}
	return 2;
}

void GameOverMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(endGame, states);
	target.draw(again, states);
	target.draw(exit, states);
	target.draw(triangle, states);
}