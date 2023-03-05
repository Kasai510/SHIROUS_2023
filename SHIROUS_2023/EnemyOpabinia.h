#pragma once
#include "Enemy.h"
class EnemyOpabinia :
    public Enemy
{
public:
	EnemyOpabinia(Battle* battle, const Vec2& p);
	void update();
	void move();
	void draw();
private:
	Vec2 mouth_pos;
};

