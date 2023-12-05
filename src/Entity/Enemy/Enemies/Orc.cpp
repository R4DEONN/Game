#include "Orc.h"

Orc::Orc(const sf::Vector2f& position)
: Enemy("../res/orc.png", position)
{
	type = EnemyType::ORC;
}
