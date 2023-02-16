#pragma once
#include "Enemy.h"
class EnemyPikaia :
    public Enemy
{
public:
	EnemyPikaia(Battle* battle, Vec2 p);

	void update();
};

