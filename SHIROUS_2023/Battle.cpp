#include"Battle.h"
#include"EnemyPikaia.h"
#include"EnemyKurage.h"
#include"EnemyShotPikaia.h"
#include"EnemyHallucigenia.h"
#include"EnemyOpabinia.h"

Battle::Battle()
{
	stages << Stage_object(this, { -100,1000 , 19200+200, 200 });

	stages << Stage_object(this, { 1800,1000 }, 200, 200);
	stages << Stage_object(this, { 3000,300 }, 200, 200);
	stages << Stage_object(this, { 4500,1000 }, 200, 300);
	stages << Stage_object(this, { 5000,200 }, 200, 500);
	stages << Stage_object(this, { 7000,1000 }, 200, 500);
	stages << Stage_object(this, { 8500,1000 }, 200, 200);
	stages << Stage_object(this, { 12000,200 }, 200, 500);
	stages << Stage_object(this, { 12000,1000 }, 200, 600);

	//stages << Stage_object(this, { 800,600 }, 200, 200);
	//stages << Stage_object(this, { 1400,600 }, 200, 200);
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
	//アイテムの更新。
	if(MouseL.down())items << std::make_shared<ItemLP>(this, camera.windowpos_in_camera(Cursor::Pos()), 10);
	for (auto& item : items) {
		item->update();
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
	//オプションの攻撃

	
	
	
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
	enemies.remove_if([](const std::shared_ptr<Enemy>& enemy) {if(enemy->is_dead()) return enemy->is_dead(); });

	//item削除
	items.remove_if([](const std::shared_ptr<Item>& item) {return item->is_dead(); });
	
	//camera.scroll(Vec2(2,0));//強制横スクロール
	camera.set(player.get_pos());

	//for debug
	camera_control();
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
	for (auto& item : items) {
		item->draw();
	}
	

	for (int i = 0; i < stages.size(); i++)
	{
		stages[i].draw(camera);
	}
	
	camera.draw_stage_area();

	draw_UI();
	debug_draw();
}
void Battle::draw_UI()
{
	camera.draw_texture(RectF{ Arg::center(camera.get_center().movedBy(0,-465)),1920,150 }, Palette::Black);
	camera.draw_texture(font30(U"HP"), camera.get_center().movedBy(-1920 / 2 + 50, -500));
	camera.draw_texture(font30(U"LP"), camera.get_center().movedBy(-1920 / 2 + 50, -430));

	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -500), player.get_Max_HP(), 20 }, Palette::Gray);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -500), player.get_HP(), 20 }, Palette::Lightgreen);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -430), player.get_Max_LP(), 20 }, Palette::Gray);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -430), player.get_LP(), 20 }, Palette::Lightgreen);

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

void Battle::initialize_enemies()
{
	enemies << std::make_shared<EnemyKurage>(this, Vec2(2400, 400));
	enemies << std::make_shared<EnemyKurage>(this, Vec2(4000, 400));
	enemies << std::make_shared<EnemyKurage>(this, Vec2(4100, 300));
	enemies << std::make_shared<EnemyKurage>(this, Vec2(4200, 600));
	enemies << std::make_shared<EnemyHallucigenia>(this, Vec2(5700, 950));
	enemies << std::make_shared<EnemyPikaia>(this, Vec2(6500, 300));
	enemies << std::make_shared<EnemyHallucigenia>(this, Vec2(6700, 950));
	enemies << std::make_shared<EnemyPikaia>(this, Vec2(9500, 300));
	enemies << std::make_shared<EnemyPikaia>(this, Vec2(9600, 200));
	enemies << std::make_shared<EnemyPikaia>(this, Vec2(9800, 400));

	//enemys << std::make_shared<EnemyPikaia>(battle, Vec2(2100,500));
	//enemies << std::make_shared<EnemyHallucigenia>(this, Vec2(2000, 600));
	//enemies << std::make_shared<EnemyKurage>(this, Vec2(1700, 400));
	//enemies << std::make_shared<EnemyPikaia>(this, Vec2(2000, 400));
	//enemies << std::make_shared<EnemyOpabinia>(this, Vec2(2000, 200));
}

void Battle::add_draw_objects(std::shared_ptr<BattleObject>)
{
	//draw_order順に配列に組み込まれるような処理
}
