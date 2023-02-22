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
	hit_box = hit_box_origin.moveBy(pos);
	time++;
}

void EnemyShot::move()
{
	pos += v;
}
