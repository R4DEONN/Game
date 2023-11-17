#include "Menu.h"
#include "../../Common/GameConstants.h"

const sf::Vector2f DEFAULT_POSITION = {
	0.5f * sf::VideoMode::getDesktopMode().width,
	0.45f * sf::VideoMode::getDesktopMode().height,
};

const sf::Vector2f SELECTED_MARGIN = { 30, 0 };

const float INDENT = BLOCK_SIZE / 3 + 20;

const sf::Vector2f leveler = {0, BLOCK_SIZE / 5};

Menu::Menu(const std::wstring strings[], int count)
{
	selectedId = 0;
	triangle.setOutlineColor(sf::Color::White);
	triangle.setOutlineThickness(2);
	triangle.setFillColor(sf::Color::Black);
	triangle.setPointCount(3);
	triangle.setPoint(0, { 0, -8 });
	triangle.setPoint(1, { 0, 8 });
	triangle.setPoint(2, { 15, 0 });

	font.loadFromFile("../res/Minecraft Rus NEW.otf");
	for (int i = 0; i < count; i++)
	{
		auto text = std::make_shared<sf::Text>(strings[i], font, BLOCK_SIZE / 3);
		text->setFillColor(sf::Color::White);
		const sf::Vector2f delta = { i == 0 ? text->getLocalBounds().width / 2 : texts[0]->getLocalBounds().width / 2, 0 };
		const sf::Vector2f indent = {0, i * INDENT};
		text->setPosition(DEFAULT_POSITION - delta + indent);
		texts.push_back(text);
	}

	triangle.setPosition(texts[selectedId]->getPosition() + leveler);
	texts[selectedId]->setPosition(texts[selectedId]->getPosition() + SELECTED_MARGIN);
}

int Menu::update(float elapsedSeconds)
{
	delay -= elapsedSeconds;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && delay <= 0)
	{
		delay = 0.15;
		if (selectedId >= texts.size() - 1)
		{
			return -1;
		}
		selectedId++;
		texts[selectedId - 1]->setPosition(
			texts[selectedId - 1]->getPosition() - SELECTED_MARGIN
		);
		triangle.setPosition(texts[selectedId]->getPosition() + leveler);
		texts[selectedId]->setPosition(
			texts[selectedId]->getPosition() + SELECTED_MARGIN
		);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && delay <= 0)
	{
		delay = 0.15;
		if (selectedId <= 0)
		{
			return -1;
		}
		selectedId--;
		texts[selectedId + 1]->setPosition(
			texts[selectedId + 1]->getPosition() - SELECTED_MARGIN
		);
		triangle.setPosition(texts[selectedId]->getPosition() + leveler);
		texts[selectedId]->setPosition(
			texts[selectedId]->getPosition() + SELECTED_MARGIN
		);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		return selectedId;
	}
	return -1;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(triangle, states);
	for (const auto& text: texts)
	{
		target.draw(*text, states);
	}
}
