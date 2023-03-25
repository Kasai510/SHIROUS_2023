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

	//モーションパターンの作成
	create_motion_patarn();

	now_motion_patarns_index = 0;

	now_motion_patarn_num = motion_patarns[now_motion_patarns_index].size();
	now_motion_patarn_index = 0;
	now_motion_kind = motion_patarns[now_motion_patarns_index][now_motion_patarn_index];
	init_motion();
}

void EnemyAnomalocaris::update()
{

	update_motion();//モーションの更新

	if (hp <= 0) {
		dead = true;
	}
	time++;
}


void EnemyAnomalocaris::init_motion()
{
	Console << now_motion_kind;

	switch (now_motion_kind)
	{
	case EnemyAnomalocaris::motion_kind_standby:
		init_motion_standby();
		break;
	case EnemyAnomalocaris::motion_kind_hurtle:
		init_motion_hurtle();
		break;
	case EnemyAnomalocaris::motion_kind_shot1:
		init_motion_shot1();
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
	case EnemyAnomalocaris::motion_kind_shot1:
		update_motion_shot1();
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
	case EnemyAnomalocaris::motion_kind_shot1:
		draw_motion_shot1();
		break;
	default:
		break;
	}
}

void EnemyAnomalocaris::change_motion(Motion_Kind next_motion_kind)
{
	now_motion_kind = next_motion_kind;
	motion_timer = 0.0;
	motion_phase = 0;
	motion_counter = 0;
	motion_bool = false;

	switch (now_motion_kind)
	{
	case EnemyAnomalocaris::motion_kind_standby:
		init_motion_standby();
		break;
	case EnemyAnomalocaris::motion_kind_hurtle:
		init_motion_hurtle();
		break;
	case EnemyAnomalocaris::motion_kind_shot1:
		init_motion_shot1();
		break;
	default:
		break;
	}
}
void EnemyAnomalocaris::change_motion()
{
	now_motion_patarn_index++;
	if (now_motion_patarn_index < now_motion_patarn_num)
	{
		//次のモーションに移動
		
	}
	else
	{
		//次のモーションパターンに移動
		change_motion_patarn();
	}

	now_motion_kind = motion_patarns[now_motion_patarns_index][now_motion_patarn_index];
	motion_timer = 0.0;
	motion_phase = 0;
	motion_counter = 0;
	motion_bool = false;


	init_motion();
}

void EnemyAnomalocaris::change_motion_patarn()
{
	now_motion_patarns_index++;
	if (now_motion_patarns_index >= motion_patarns_num)
	{
		now_motion_patarns_index = 0;
	}

	now_motion_patarn_num = motion_patarns[now_motion_patarns_index].size();
	now_motion_patarn_index = 0;

}

void EnemyAnomalocaris::create_motion_patarn()
{

	String csv_name = U"data/csv/Anomalocaris/motiondata.csv";//読み込むファイルの名前

	//CSVファイル
	CSV motion_data(csv_name);
	if (!motion_data) {
		throw Error(U"Failed to load 'motion_data.csv'");
	}

	Array<Motion_Kind> motion_patarn;
	//縦
	for (int y = 0; y < motion_data.rows() - 1; y++)
	{
		int x = 0;

		motion_patarn.clear();

		while (Parse<int>(motion_data[y][x]) != -1)
		{
			motion_patarn << Motion_Kind(Parse<int>(motion_data[y][x]));
			x++;
		}

		motion_patarns << motion_patarn;
	}

	motion_patarns_num = motion_patarns.size();
	
}

