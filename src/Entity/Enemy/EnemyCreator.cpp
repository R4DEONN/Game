#include "EnemyCreator.h"
#include "Enemies/Orc.h"

std::shared_ptr<IEnemy> EnemyCreator::createEnemy(EnemyType type, sf::Vector2f position)
{
	switch (type)
	{
	case EnemyType::ORC:
		return std::make_shared<Orc>(position);
	}
}