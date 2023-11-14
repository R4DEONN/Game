#ifndef _GAMECONSTANTS_H_
#define _GAMECONSTANTS_H_

#include "SFML/Graphics.hpp"

static const float BLOCK_SIZE = sf::VideoMode::getDesktopMode().height / 1.5 / 16;
static const float CENTER_OFFSET_X = (sf::VideoMode::getDesktopMode().width - BLOCK_SIZE * 16) / 2;
static const float CENTER_OFFSET_Y = (sf::VideoMode::getDesktopMode().height - BLOCK_SIZE * 16) / 2;

#endif //_GAMECONSTANTS_H_
