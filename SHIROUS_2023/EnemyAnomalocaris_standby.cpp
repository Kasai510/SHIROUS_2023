#include"EnemyAnomalocaris.h"
#include"Battle.h"


//待機
void EnemyAnomalocaris::init_motion_standby()
{

}

void EnemyAnomalocaris::update_motion_standby()
{
	motion_timer += battle->get_scene_del();

	if (motion_timer >= 1.5)
	{
		//一定時間たったら次のモーションに移行
		//change_motion(Motion_Kind(Random(1, motion_kind_num - 1)));
		change_motion();
	}

}

void EnemyAnomalocaris::draw_motion_standby()
{
	battle->get_camera().draw_texture(RectF(Arg::center(pos), width, height), Palette::Yellow);
	battle->get_camera().draw_texture(TextureAsset(U"anomalocaris"), pos);
	
}
