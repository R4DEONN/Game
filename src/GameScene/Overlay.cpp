//
// Created by admin on 14.11.2023.
//

#include "Overlay.h"
#include "../Common/GameConstants.h"

Overlay::Overlay(float SecondsToEnd, int PlayerHealth)
{
	healthTexture.loadFromFile("../res/head.png");
	healthShape.setTexture(&healthTexture);
	healthShape.setSize({
		BLOCK_SIZE,
		BLOCK_SIZE
	});
	healthShape.setPosition({
		CENTER_OFFSET_X - float(2.2 * BLOCK_SIZE),
		CENTER_OFFSET_Y + float(1.5 * BLOCK_SIZE)
	});
	font.loadFromFile("../res/Minecraft Rus NEW.otf");
	healthPoints.setFont(font);
	healthPoints.setFillColor(sf::Color::White);
	healthPoints.setCharacterSize(BLOCK_SIZE / 2);
	healthPoints.setPosition({
		CENTER_OFFSET_X - float(1.2 * BLOCK_SIZE),
		CENTER_OFFSET_Y + float(1.7 * BLOCK_SIZE)
	});
	healthPoints.setString("x" + std::to_string(PlayerHealth));

	fps.setFont(font);
	fps.setFillColor(sf::Color::White);
	fps.setCharacterSize(BLOCK_SIZE / 3);
	fps.setPosition({
		CENTER_OFFSET_X - 2 * BLOCK_SIZE,
		CENTER_OFFSET_Y + float(3 * BLOCK_SIZE)
	});
	fps.setString("fps " + std::to_string(0));

	currentItemFieldTexture.loadFromFile("../res/itemField.png");
	currentItemField.setTexture(&currentItemFieldTexture);
	currentItemField.setSize({
		float(BLOCK_SIZE * 1.375),
		float(BLOCK_SIZE * 1.375),
	});
	currentItemField.setPosition({
		CENTER_OFFSET_X - float(BLOCK_SIZE * 1.375) / 2 - 15,
		CENTER_OFFSET_Y + float(BLOCK_SIZE * 1.375) / 2
	});
	currentItemField.setOrigin({
		float(BLOCK_SIZE * 1.375) / 2,
		float(BLOCK_SIZE * 1.375) / 2,
	});

	clockTexture.loadFromFile("../res/clock.png");
	clockShape.setTexture(&clockTexture);
	clockShape.setSize({
		static_cast<float>(BLOCK_SIZE / 1.5),
		static_cast<float>(BLOCK_SIZE / 1.5)
	});
	clockShape.setPosition({
		CENTER_OFFSET_X,
		static_cast<float>(CENTER_OFFSET_Y - BLOCK_SIZE / 1.5 - 9)
	});

	timeLine.setSize({
			BLOCK_SIZE * 16 - float(BLOCK_SIZE / 1.5) - 9,
			BLOCK_SIZE / 4
	});
	timeLine.setPosition({
			CENTER_OFFSET_X + float(BLOCK_SIZE / 1.5) + 9,
			CENTER_OFFSET_Y - float(BLOCK_SIZE / 1.5) + 10
	});
	timeLine.setFillColor({149, 189, 36});
}

void Overlay::update(float secondsToEnd, int playerHealth, float elapsedTime)
{
	timeLine.setSize({
			(BLOCK_SIZE * 16 - float(BLOCK_SIZE / 1.5) - 9) * secondsToEnd / 100,
			BLOCK_SIZE / 4
	});
	healthPoints.setString("x" + std::to_string(playerHealth));
	fps.setString("fps " + std::to_string(int(1.f / elapsedTime)));
}

void Overlay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(healthShape, states);
	target.draw(healthPoints, states);
	target.draw(clockShape, states);
	target.draw(timeLine, states);
	target.draw(currentItemField, states);
	target.draw(fps, states);
}
