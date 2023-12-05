#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Entity.h"
#include "../../Common/Direction.h"
#include "../Player/Player.h"
#include "IEnemy.h"
#include "EnemyType.h"

class Enemy : public IEnemy
{
 public:
	Enemy(const std::string& texturePath, sf::Vector2f position);
	void update(float elapsedTime, Field& field, std::vector<std::shared_ptr<IEnemy>>& enemies, sf::Vector2f playerPosition);
	EntityType getType() override;
	sf::RectangleShape getShape() const override;
	int getHealth() override;
	sf::Vector2f getPosition() override;
	Direction& getMoveDirection() override;
	float getMoveTimer() override;
	void setSpeed(float newSpeed) override;
	void setHealth(int newHealth) override;
	void setMoveTimer(float newTime) override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Entity entity;
	void updateDirection(Direction& moveDirection, sf::Vector2f playerPosition);
	void handleEnemiesCollision(sf::Vector2f& movement, std::vector<std::shared_ptr<IEnemy>>& enemies);
protected:
	EnemyType type = EnemyType::ORC;
};

#endif //_ENEMY_H_
