#include"Battle.h"
#include"EnemyPikaia.h"
#include"EnemyKurage.h"
#include"EnemyShotPikaia.h"
#include"EnemyHallucigenia.h"

Battle::Battle()
{
	stages << Stage_object({ 800,600 }, 200, 200);
	stages << Stage_object({ 1400,600 }, 200, 200);
	stages << Stage_object({ -100,900 , 19200+200, 200 });
	initialize_enemies();//これはのちにEnemiesManagerとかがするかも知れない
}

void Battle::update()
{

	scene_del = Scene::DeltaTime();

	//状態の更新。
	//プレイヤーの更新。
	player.update();
	//エネミーの更新。
	for (auto& enemy : enemies) {
		enemy->update();
	}
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
	
	for (auto& e : enemies) {
		for (int i = 0; i < stages.size(); i++)
		{
			e->move_intersect_stage(stages[i]);
		}
	}
	
	


	//攻撃の追加
	//自機は攻撃しない
	/*if (player.ready_shot())
	{
		player_shots << player.shot();
	}*/
	//オプションの攻撃

	for (int i = 0; i < player.get_opt_size(); i++)
	{
		if (player.ready_opt_shot(i))
		{
			//player_shots << player.opt_shot(i);
		}
	}
	
	
	//攻撃の更新
	for (int i = 0; i < player_shots.size(); i++)
	{
		player_shots[i]->update();

	}
	//enemyshot_update
	for (auto& e : enemy_shots) {
		e->update();
	}
	for (auto& e : effects) {
		e->update();
	}

	//画面外に出た攻撃の消去。壁などに当たった弾も。
	for (int i = 0; i < player_shots.size(); i++)
	{
		//判定。
	}
	player_shots.remove_if([](const std::shared_ptr<Shot>& p) {return (p->get_over()); });
	enemy_shots.remove_if([](const std::shared_ptr<Shot>& p) {return (p->get_over()); });
	effects.remove_if([](const std::unique_ptr<myIEffect>& p) {return (p->isdead()); });
	//攻撃の当たり判定
	
	//enemy死
	enemies.remove_if([](const std::shared_ptr<Enemy>& enemy) {return enemy->is_dead(); });
	
	//camera.scroll(Vec2(2,0));//強制横スクロール
	camera.set(player.get_pos());


	//camera control
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

void Battle::draw()
{
	//背景
	background.draw();

	

	//敵描画
	for (auto& e : enemies) {
		e->draw();
	}

	player.draw_back();
	player.draw();
	player.draw_front();

	for (int i = 0; i < player_shots.size(); i++)
	{
		player_shots[i]->draw();
	}
	for (auto& e : enemy_shots) {
		e->draw();
	}
	for (auto& e : effects) {
		e->draw();
	}

	for (int i = 0; i < stages.size(); i++)
	{
		stages[i].draw(camera);
	}
	
	camera.draw_stage_area();

	debug_draw();
}

void Battle::debug_draw()
{
	//Print << player_shots.size();
	font30(camera.windowpos_in_camera(Cursor::Pos()).asPoint()).draw(Cursor::Pos());
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

void Battle::initialize_enemies()
{
	//enemys << std::make_shared<EnemyPikaia>(battle, Vec2(2100,500));
	enemies << std::make_shared<EnemyHallucigenia>(this, Vec2(2000, 600));
	enemies << std::make_shared<EnemyKurage>(this, Vec2(1700, 400));
	enemies << std::make_shared<EnemyPikaia>(this, Vec2(2000, 400));
}
