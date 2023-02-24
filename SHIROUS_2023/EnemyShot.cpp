#include "stdafx.h"
#include"Enemy.h"
#include "EnemyShot.h"

EnemyShot::EnemyShot(Battle* battle, const Vec2& p):Shot(battle,p)
{
}

EnemyShot::EnemyShot(Battle* battle,const  Vec2& p,  const std::shared_ptr<class Fish>& s_master) :Shot(battle, p)
{
	w_master = s_master;
}

void EnemyShot::update()
{
	move();
	for (int i : step(hit_boxs.size())) {
		update_hit_box(i, pos);
	}
	time++;
}

void EnemyShot::move()
{
	pos += v;
}
