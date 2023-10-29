#ifndef _GAMECONSTANTS_H_
#define _GAMECONSTANTS_H_

#include <SFML/Graphics.hpp>

class GameConstants
{
 public:
	inline static float BLOCK_SIZE = sf::VideoMode::getDesktopMode().height / 16;
};

#endif //_GAMECONSTANTS_H_
