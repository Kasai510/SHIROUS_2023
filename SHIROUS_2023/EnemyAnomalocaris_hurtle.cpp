#include"EnemyAnomalocaris.h"
#include"Battle.h"
#include"myIEffectBubble.h"

//突進

void EnemyAnomalocaris::init_motion_hurtle()
{
	motion_phase = 0;
	start_pos = pos;
}

void EnemyAnomalocaris::update_motion_hurtle()
{
	motion_timer += battle->get_scene_del();
	if (motion_phase == 0)
	{
		//突進の道筋を表示
		if (motion_timer >= 2)
		{
			motion_phase = 1;
			motion_timer = 0;
		}
	}
	else if (motion_phase == 1)
	{
		//突進
		pos.x -= 3000 * battle->get_scene_del();
		if (motion_timer >= 2 && battle->get_camera().in_camera(pos + Vec2{width/2,0}) == false)
		{
			motion_phase = 2;
			motion_timer = 0;
			//上に置いておく
			pos = start_pos + Vec2{ 0,-600 - height };
		}

		//ダメージ
		if (battle->get_player().get_rect().intersects(get_rect())) {
			battle->get_player().damage(10);
		}

		if (RandomBool(0.7))
		{
			battle->get_effects() << std::make_unique<myIEffectBubble>(battle, pos + RandomVec2() * Random() * 100, Random() * 15, HSV(Random(0, 150)));
		}
	}
	else if (motion_phase == 2)
	{
		if (motion_timer >= 2)
		{
			//徐々に下に降りる
			pos.y += 400 * battle->get_scene_del();
			if (abs(pos.y - start_pos.y) <= 10)
			{

				pos = start_pos;
				//change_motion(motion_kind_standby);
				change_motion();
			}
		}
	
	}
}

void EnemyAnomalocaris::draw_motion_hurtle()
{
	if (motion_phase == 0)
	{
		//突進の道筋を表示
	
		battle->get_camera().draw_texture(RectF(pos - Vec2{ 2500,height / 2 }, 2500, height), HSV(1, 1, 1,0.1+ 0.6 * sin(360_deg * motion_timer)));
		battle->get_camera().draw_texture(RectF(Arg::center(pos), width, height), Palette::Yellow);
	}
	else if (motion_phase == 1)
	{
		battle->get_camera().draw_texture(RectF(Arg::center(pos), width, height), Palette::Yellow);
		
	}
	else if (motion_phase == 2)
	{
		battle->get_camera().draw_texture(RectF(Arg::center(pos), width, height), Palette::Yellow);
	}

}
