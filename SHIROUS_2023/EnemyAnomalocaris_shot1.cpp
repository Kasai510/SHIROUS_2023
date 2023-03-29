#include"EnemyAnomalocaris.h"
#include"EnemyShotAnomalocaris1.h"
#include"Battle.h"


//待機
void EnemyAnomalocaris::init_motion_shot1()
{
	motion_phase = 0;
}

void EnemyAnomalocaris::update_motion_shot1()
{
	motion_timer += battle->get_scene_del();

	if (motion_phase == 0)
	{
		//
		if (motion_timer >= 1.5)
		{
			motion_counter = 1;
			motion_timer = 0;
			motion_phase = 1;


		}
	}
	else if (motion_phase == 1)
	{
		if (motion_timer >= 0.7)
		{
			motion_timer = 0;

			//double shot_arg = 90_deg + 30_deg * motion_counter;

			double shot_arg =   atan2(battle->get_player().get_pos().y - pos.y, battle->get_player().get_pos().x - pos.x);

			//Vec2 spon_pos = get_pos_left()  + 220 * Vec2{cos(90_deg+30_deg*motion_counter),sin(90_deg + 30_deg * motion_counter)};
			Vec2 spon_pos = get_pos_left() + Vec2{ -100,0 };

			battle->get_ememy_shots() << std::make_shared<EnemyShotAnomalocaris1>(battle, spon_pos, shot_arg);
			
			if (motion_counter == 5)
			{
				//change_motion(motion_kind_standby);
				change_motion();
			}

			motion_counter++;
		}
	}

}

void EnemyAnomalocaris::draw_motion_shot1()
{
	battle->get_camera().draw_texture(RectF(Arg::center(pos), width, height), Palette::Yellow);

}
