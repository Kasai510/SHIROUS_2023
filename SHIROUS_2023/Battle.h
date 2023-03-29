﻿#pragma once
#include"myCamera.h"
# include"Player.h"
#include"Enemy.h"
#include"StageObject.h"
#include"OptionShirousShot.h"
#include"myIEffect.h"
#include"Background.h"
#include"ItemLP.h"

//敵のデータ
struct Enemy_Data
{

	int enemy_kind;
	Vec2 spon_pos;

	// シリアライズに対応させるためのメンバ関数を定義する
	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(enemy_kind,spon_pos);
	}
};

class Battle
{
private:
	double scene_del;//前のフレームからの経過時間
	Vec2 scene_size{ Scene::Size() };//シーンの大きさ

	

	Array<Enemy_Data> enemy_datas;
	bool now_map_make{ false };//map_make中かどうか
	int stage_index{ 1 };
	Enemy_Kind select_enemy_kind;//配置する敵の種類
	//Stage_object select_stage_object;//配置するobject

	int scene_num = 2;
	int change_scene_to = -1;

	myCamera camera = myCamera(this);

	Player player{ this, {400,400} };
	Array<std::shared_ptr<Shot>> player_shots;
	Array<std::shared_ptr<Shot>> enemy_shots;

	//敵配列
	Array<std::shared_ptr<Enemy>> enemies;

	Array<Stage_object> stages;
	Font font30{ 30 };
	Font font50{ 50 };

	Array<std::unique_ptr<myIEffect>> effects;

	Array<std::shared_ptr<Item>> items;

	Array<std::weak_ptr<BattleObject>> draw_objects;

	Vec2 camera_control_down_p;
	Background background{this};

public:
	Battle();
	~Battle();
	void update();
	void draw();
	void draw_UI();
	void debug_draw();//デバッグ用のdraw
	Font getFont30() { return font30; };
	void camera_control();

	bool change_scene_check();
	int change_scene();

	void initialize_enemies();
	void save_enemies();

	

	void update_map_make();
	void draw_map_make();


	Vec2 get_scene_size() { return scene_size; }
	double get_scene_del() { return scene_del; }
	myCamera& get_camera() { return camera; }
	Player& get_player() { return player; }
	Array<std::shared_ptr<Shot>>& get_player_shots() { return player_shots; }
	Array<std::shared_ptr<Shot>>& get_ememy_shots() { return enemy_shots; }
	Array<std::shared_ptr<Enemy>>& get_enemies() { return enemies; }
	Array<Stage_object>& get_stages() { return stages; }
	Array<std::unique_ptr<myIEffect>>& get_effects() { return effects; }
	Array<std::shared_ptr<Item>>& get_items() { return items; }
	void add_draw_objects(std::shared_ptr<BattleObject>);
};
