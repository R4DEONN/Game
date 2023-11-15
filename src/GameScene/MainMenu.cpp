//
// Created by admin on 15.11.2023.
//

#include "MainMenu.h"
#include "../Common/GameConstants.h"

MainMenu::MainMenu()
{
	logoTexture.loadFromFile("../res/JOPK_logo_RU.png");
	logoShape.setTexture(&logoTexture);
	logoShape.setPosition({
		0.5f * sf::VideoMode::getDesktopMode().width,
		0.3f * sf::VideoMode::getDesktopMode().height,
	});
	logoShape.setSize({
		static_cast<float>(BLOCK_SIZE * 6.5),
		static_cast<float>(BLOCK_SIZE * 5.2),
	});
	logoShape.setOrigin({
		logoShape.getSize().x / 2,
		logoShape.getSize().y / 2,
	});

	triangle.setOutlineColor(sf::Color::White);
	triangle.setOutlineThickness(2);
	triangle.setFillColor(sf::Color::Black);
	triangle.setPointCount(3);
	triangle.setPoint(0, {0, -8});
	triangle.setPoint(1, {0, 8});
	triangle.setPoint(2, {15, 0});

	font.loadFromFile("../res/Minecraft Rus NEW.otf");
	beginGame.setFont(font);
	beginGame.setFillColor(sf::Color::White);
	beginGame.setCharacterSize(BLOCK_SIZE / 3);
	beginGame.setString(L"Начать игру");
	beginGame.setPosition({
		0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2 + triangle.getLocalBounds().width + 10,
		0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2),
	});

	exitGame.setFont(font);
	exitGame.setFillColor(sf::Color::White);
	exitGame.setCharacterSize(BLOCK_SIZE / 3);
	exitGame.setString(L"Выйти из игры");
	exitGame.setPosition({
		0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
		0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 3 + 20,
	});

	triangle.setPosition({
			0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
			0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6,
	});
}

int MainMenu::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		triangle.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6 + BLOCK_SIZE / 3 + 20,
		});
		exitGame.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2 + triangle.getLocalBounds().width + 10,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 3 + 20,
		});

		beginGame.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2),
		});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		triangle.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 6,
		});
		exitGame.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2) + BLOCK_SIZE / 3 + 20,
		});

		beginGame.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2 + triangle.getLocalBounds().width + 10,
				0.25f * sf::VideoMode::getDesktopMode().height + static_cast<float>(BLOCK_SIZE * 6.2),
		});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		const float triangleY = triangle.getPosition().y;
		triangle.setPosition({
				0.5f * sf::VideoMode::getDesktopMode().width - beginGame.getLocalBounds().width / 2,
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

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(logoShape, states);
	target.draw(beginGame, states);
	target.draw(exitGame, states);
	target.draw(triangle, states);
}
