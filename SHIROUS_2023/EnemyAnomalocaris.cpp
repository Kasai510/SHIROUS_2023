#include "stdafx.h"
#include "EnemyAnomalocaris.h"
#include"Battle.h"

EnemyAnomalocaris::EnemyAnomalocaris(Battle* battle, const Vec2& p) :Enemy(battle, p)
{
	image_name = U"anomalocaris";
	image_size_int = 300;
	speed = { -5,0 };
	width = 400;
	height = 500;
	hp = 100;
	start_pos = pos;
}

void EnemyAnomalocaris::update()
{

	update_motion();//モーションの更新

	if (hp <= 0) {
		dead = true;
	}
	time++;
}

void EnemyAnomalocaris::change_motion(Motion_Kind next_motion_kind)
{
	now_motion_kind = next_motion_kind;
	motion_timer = 0.0;
	motion_phase =  0;
	motion_bool= false;

	switch (now_motion_kind)
	{
	case EnemyAnomalocaris::motion_kind_standby:
		init_motion_standby();
		break;
	case EnemyAnomalocaris::motion_kind_hurtle:
		init_motion_hurtle();
		break;
	default:
		break;
	}
}

void EnemyAnomalocaris::init_motion()
{
	switch (now_motion_kind)
	{
	case EnemyAnomalocaris::motion_kind_standby:
		init_motion_standby();
		break;
	case EnemyAnomalocaris::motion_kind_hurtle:
		init_motion_hurtle();
		break;
	default:
		break;
	}
}

void EnemyAnomalocaris::update_motion()
{
	switch (now_motion_kind)
	{
	case EnemyAnomalocaris::motion_kind_standby:
		update_motion_standby();
		break;
	case EnemyAnomalocaris::motion_kind_hurtle:
		update_motion_hurtle();
		break;
	default:
		break;
	}
}

void EnemyAnomalocaris::draw()
{

	draw_motion();
	
}

void EnemyAnomalocaris::draw_motion()
{
	switch (now_motion_kind)
	{
	case EnemyAnomalocaris::motion_kind_standby:
		draw_motion_standby();
		break;
	case EnemyAnomalocaris::motion_kind_hurtle:
		draw_motion_hurtle();
		break;
	default:
		break;
	}
}
