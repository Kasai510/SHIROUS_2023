﻿#include"Battle.h"

Battle::Battle()
{
	stages << Stage_object({ 800,600 }, 200, 200);
	stages << Stage_object({ 1400,600 }, 200, 200);
}

void Battle::update()
{
	//状態の更新。
	//プレイヤーの更新。
	player.update();
	//エネミーの更新。
	
	//ステージの更新。
	for (int i = 0; i < stages.size(); i++)
	{
		stages[i].update();
	}
	

	//移動後の衝突処理。ぶつかっていたり通り抜けていたりしたら、修正する
	//ステージの限界
	player.check_limit_stage(camera);

	//stageの壁・床
	for (int i = 0; i < stages.size(); i++)
	{
		player.move_intersect_stage(stages[i]);
	}



	//攻撃の追加
	/*if (player.ready_shot())
	{
		player_shots << player.shot();
	}*/
	for (int i = 0; i < player.get_opt_size(); i++)
	{
		if (player.ready_opt_shot(i))
		{
			player_shots << player.opt_shot(i);
		}
	}
	
	//攻撃の更新
	for (int i = 0; i < player_shots.size(); i++)
	{
		player_shots[i].update();

	}
	//画面外に出た攻撃の消去。壁などに当たった弾も。
	for (int i = 0; i < player_shots.size(); i++)
	{
		//判定。
	}
	player_shots.remove_if([](Player_shot p) {return (p.get_over()); });

	//攻撃の当たり判定
	


	//camera.scroll(Vec2(2,0));//強制横スクロール
	camera.set(player.get_pos());
}

void Battle::draw()
{
	for (int i = 0; i < stages.size(); i++)
	{
		stages[i].draw(camera);
	}

	player.draw_back(camera);
	player.draw(camera);
	player.draw_front(camera);

	for (int i = 0; i < player_shots.size(); i++)
	{
		player_shots[i].draw(camera);
	}

	camera.draw_stage_area();
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
