#ifndef _GAMECONSTANTS_H_
#define _GAMECONSTANTS_H_

#include "SFML/Graphics.hpp"

class GameConstants
{
 public:
	inline static const float BLOCK_SIZE = sf::VideoMode::getDesktopMode().height / 1.5 / 16;
	inline static const float CENTER_OFFSET_X = (sf::VideoMode::getDesktopMode().width - BLOCK_SIZE * 16) / 2;
	inline static const float CENTER_OFFSET_Y = (sf::VideoMode::getDesktopMode().height - BLOCK_SIZE * 16) / 2;
};

#endif //_GAMECONSTANTS_H_
