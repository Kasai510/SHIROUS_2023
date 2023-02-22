#pragma once
#include"myCamera.h"
# include"Player.h"
#include"Enemy.h"
#include"EnemyColony.h"
#include"StageObject.h"
#include"OptionShirousShot.h"



//{ 1920,1080 }

class Battle
{
private:
	double scene_del;//前のフレームからの経過時間

	int scene_num = 2;
	int change_scene_to = -1;

	myCamera camera;

	Player player{ this, {400,400} };
	Array<std::shared_ptr<Shot>> player_shots;
	Array<std::shared_ptr<Shot>> enemy_shots;

	//各種敵集団のコロニーの配列
	Array<std::shared_ptr<EnemyColony>> enemy_colonys;

	Array<Stage_object> stages;
	Font font30{ 30 };


public:
	Battle();
	void update();
	void draw();
	void debug_draw();//デバッグ用のdraw

	bool change_scene_check();
	int change_scene();

	double get_scene_del() { return scene_del; }
	myCamera& get_camera() { return camera; }
	Player& get_player() { return player; }
	Array<std::shared_ptr<Shot>>& get_player_shots() { return player_shots; }
	Array<std::shared_ptr<Shot>>& get_ememy_shots() { return enemy_shots; }
	Array<std::shared_ptr<EnemyColony>>& get_enemy_colonys() { return enemy_colonys; }
	Array<Stage_object>& get_stages() { return stages; }
	
};
