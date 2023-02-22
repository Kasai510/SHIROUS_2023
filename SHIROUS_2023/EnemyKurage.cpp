#include "stdafx.h"
#include "EnemyKurage.h"

EnemyKurage::EnemyKurage(Battle* battle, Vec2 p):Enemy(battle,p)
{
	image_name = U"kurage";
	image_size_int = 300;
	speed = { 0,0 };
	width = 150;
	height = 150;
	first_level = pos.y;
}

void EnemyKurage::update()
{
	
	move();
	time++;
}

void EnemyKurage::move()
{
	if (jump_wait_time == 120) {
		jump_wait_time = 0;
		speed.y += (first_level - pos.y)*0.1;
		if (isGoRight) {
			speed.x += 4;
		}
		else {
			speed.x += -4;
		}
		isGoRight = not isGoRight;
	}
	jump_wait_time++;

	speed.y += 0.1;
	speed *= 0.9;
	prev_pos = pos;
	pos += speed;
}
