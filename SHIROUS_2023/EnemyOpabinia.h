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
	Vec2 mouth_local_pos;
	Vec2 mouth_go_local_pos;
	Vec2 mouth_v;
	bool mouth_is_open;
};

