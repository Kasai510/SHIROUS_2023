#include "stdafx.h"
#include "EnemyShotAnomalocaris1.h"
#include"myIEffectClash.h"
#include "Battle.h"

EnemyShotAnomalocaris1::EnemyShotAnomalocaris1(Battle* battle, const Vec2& p,double shot_arg)
	:EnemyShot(battle, p)
{
	this->shot_arg = shot_arg;
	can_move = false;
	hit_r = 10;
	hit_c = Circle(pos, hit_r);
}


void EnemyShotAnomalocaris1::update()
{

	time += battle->get_scene_del();
	if (can_move)
	{
		move();
	
	}
	else
	{
		hit_r += 30 * battle->get_scene_del();
		if (hit_r >= 30)
		{
			can_move = true;
		}
	}


	hit_c = Circle(pos, hit_r);

	//壁との当たり判定
	for (auto& stage_object : battle->get_stages())
	{
		if (hit_c.intersects(stage_object.get_rect()))
		{
			battle->get_effects() << std::make_unique<myIEffectClash>(battle, pos, HSV(272, 1, 1));
			over = true;
		}
	}

	//player
	if (battle->get_player().get_rect().intersects(hit_c))
	{
		battle->get_player().damage(10);
		battle->get_effects() << std::make_unique<myIEffectClash>(battle, pos, HSV(272, 1, 1));
		over = true;
	}

	//画面外
	if (not battle->get_camera().in_camera(hit_c))
	{
		over = true;
	}
}

void EnemyShotAnomalocaris1::move()
{
	pos += 2400 * Vec2{cos(shot_arg),sin(shot_arg)}*battle->get_scene_del();	
}

void EnemyShotAnomalocaris1::draw()
{
	battle->get_camera().draw_texture(hit_c, HSV(303, 1, 1));
	if (can_move)
	{
		battle->get_camera().draw_texture(hit_c, HSV(22, 1, 1));
	}
}
