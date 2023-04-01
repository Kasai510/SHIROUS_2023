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
	bool find_player;

	Vec2 mouth_local_pos;
	Vec2 mouth_go_local_pos;
	Vec2 mouth_v;
	bool mouth_is_open;
	bool is_doing_attack;
	bool attack_from_down;
	int attack_start_time;
	int8 attack_point_count;
	Array<Vec2> attack_points;
};

