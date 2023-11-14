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
		CENTER_OFFSET_X - 2 * BLOCK_SIZE,
		CENTER_OFFSET_Y + float(1.5 * BLOCK_SIZE)
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

void Overlay::update(float secondsToEnd, int playerHealth)
{
	timeLine.setSize({
			(BLOCK_SIZE * 16 - float(BLOCK_SIZE / 1.5) - 9) * secondsToEnd / 100,
			BLOCK_SIZE / 4
	});
}

void Overlay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(healthShape, states);
	target.draw(clockShape, states);
	target.draw(timeLine, states);
}
