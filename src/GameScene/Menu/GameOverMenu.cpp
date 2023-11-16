//
// Created by admin on 15.11.2023.
//

#include "GameOverMenu.h"
#include "../../Common/GameConstants.h"

const std::wstring messages[] = {
	L"Заново",
	L"Выход"
};

GameOverMenu::GameOverMenu()
	: Menu(messages, std::size(messages))
{
	title.setFont(font);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(BLOCK_SIZE / 3);
	title.setString(L"Конец игры");
	title.setPosition({
			0.5f * sf::VideoMode::getDesktopMode().width - title.getLocalBounds().width / 2,
			0.4f * sf::VideoMode::getDesktopMode().height,
	});
}

void GameOverMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(title, states);
	target.draw(triangle, states);
	for (const auto& text: texts)
	{
		target.draw(*text, states);
	}
}