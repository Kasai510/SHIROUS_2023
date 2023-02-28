#pragma once
#include "Enemy.h"
class EnemyHallucigenia :
    public Enemy
{
public:
	EnemyHallucigenia(Battle* battle,const Vec2& p);

	void update();
	void move();
	void draw();
};

