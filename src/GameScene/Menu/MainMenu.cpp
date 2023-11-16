//
// Created by admin on 15.11.2023.
//

#include "MainMenu.h"
#include "../../Common/GameConstants.h"
#include <array>

const std::wstring messages[] = {
	L"Начать игру",
	L"Выйти из игры"
};

MainMenu::MainMenu()
	: Menu(messages, std::size(messages))
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
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(logoShape, states);
	target.draw(triangle, states);
	for (const auto& text: texts)
	{
		target.draw(*text, states);
	}
}
