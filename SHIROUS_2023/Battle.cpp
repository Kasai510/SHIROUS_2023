#include"Battle.h"
#include"EnemyPikaia.h"
#include"EnemyKurage.h"
#include"EnemyShotPikaia.h"
#include"EnemyHallucigenia.h"
#include"EnemyOpabinia.h"
#include"EnemyAnomalocaris.h"


Battle::Battle()
{
	now_battle_scene = Battle_Scene::battle;

	

	init();
}

Battle::~Battle()
{

}

void Battle::init()
{
	switch (now_battle_scene)
	{
	case Battle::Battle_Scene::battle:
		init_battle();
		break;
	case Battle::Battle_Scene::map_make:
		init_map_make();
		break;
	default:
		break;
	}
}

void Battle::update()
{
	scene_del = Scene::DeltaTime();
	
	switch (now_battle_scene)
	{
	case Battle::Battle_Scene::battle:
		update_battle();
		break;
	case Battle::Battle_Scene::map_make:
		update_map_make();
		break;
	default:
		break;
	}
}



void Battle::draw()
{
	switch (now_battle_scene)
	{
	case Battle::Battle_Scene::battle:
		draw_battle();
		break;
	case Battle::Battle_Scene::map_make:
		draw_map_make();
		break;
	default:
		break;
	}

	
}

void Battle::change_battle_scene(Battle_Scene battle_scene)
{
	now_battle_scene = battle_scene;
	init();
}

void Battle::initialize()
{
	initialize_enemies();
	initialize_stage_object();
}

void Battle::save()
{
	save_enemies();
	save_stage_object();
}

void Battle::debug_draw()
{
	//Print << player_shots.size();
	font30(camera.windowpos_in_camera(Cursor::Pos()).asPoint()).draw(Cursor::Pos());
}

void Battle::camera_control()
{

	if (KeyC.pressed()) {
		double mw = Mouse::Wheel();
		if (mw > 0) {
			camera.set_scale(camera.get_scale() * 0.9);
		}
		else if (mw < 0) {
			camera.set_scale(camera.get_scale() * 1.1);
		}

		if (Key1.pressed()) {
			camera.set_scale(1);
		}
		if (Key9.pressed()) {
			camera.set_scale(0.9);
		}

		//if (MouseM.down()) {
		//	down_p = camera.windowpos_in_camera(Cursor::Pos());
		//}
		//if (MouseM.pressed()) {
		//	Vec2 add = camera.windowpos_in_camera(Cursor::Pos()) - down_p;
		//	camera.set_center(camera.get_center() + add);
		//}
	}
}

bool Battle::change_scene_check()
{
	if (change_scene_to == -1)return false;
	else return true;
}

int Battle::change_scene()
{
	int i = change_scene_to;
	change_scene_to = -1;
	return i;
}


void Battle::add_draw_objects(std::shared_ptr<BattleObject>)
{
	//draw_order順に配列に組み込まれるような処理
}
