#include"Battle.h"

void Battle::init_battle()
{

	initialize();//これはのちにEnemiesManagerとかがするかも知れない
	Deserializer<BinaryReader> reader{ U"data/binary/effect/particle_circlestar.bin" };
	if (not reader) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `data/binary/effect/particle_circlestar.bin`" };
	}
	reader(circlestar_effect);
}

void Battle::update_battle()
{
	
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
	if (MouseL.down())items << std::make_shared<ItemLP>(this, camera.windowpos_in_camera(Cursor::Pos()), 10);
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
	enemies.remove_if([](const std::shared_ptr<Enemy>& enemy) {if (enemy->is_dead()) return enemy->is_dead(); });

	//item削除
	items.remove_if([](const std::shared_ptr<Item>& item) {return item->is_dead(); });

	//camera.scroll(Vec2(2,0));//強制横スクロール
	camera.set(player.get_pos());

	//for debug
	camera_control();


	if (KeyM.down())
	{
		//map_make
		change_battle_scene(Battle_Scene::map_make);
	}
}

void Battle::draw_battle()
{
	//背景
	background.draw();

	font50(U"[M]でmap_make").draw(0, 0, Palette::Black);

	for (int i = 0; i < stages.size(); i++)
	{
		stages[i].draw(camera);
	}

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



	camera.draw_stage_area();

	draw_battle_UI();
	debug_draw();
}

void Battle::draw_battle_UI()
{
	camera.draw_texture(RectF{ Arg::center(camera.get_center().movedBy(0,-465)),1920,150 }, Palette::Black);

	camera.draw_texture(font30(U"HP"), camera.get_center().movedBy(-1920 / 2 + 50, -500));
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -500), 1000, 20 }, Palette::White);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -500), player.get_Max_HP(), 20 }, Palette::Gray);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -500), player.get_HP(), 20 }, Palette::Lightgreen);

	camera.draw_texture(font30(U"LP"), camera.get_center().movedBy(-1920 / 2 + 50, -430));
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -430), player.get_Max_LP(), 20 }, Palette::Gray);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -430), player.get_LP(), 20 }, Palette::Lightgreen);

	camera.draw_texture(font30(U"世代数"), camera.get_center().movedBy(450, -500));
	camera.draw_texture(font50(player.get_gen()), camera.get_center().movedBy(450, -440));

	camera.draw_texture(font30(U"群れ"), camera.get_center().movedBy(650, -500));
	camera.draw_texture(font50(player.get_opt_size()), camera.get_center().movedBy(650, -440));

	camera.draw_texture(font30(U"ステージ"), camera.get_center().movedBy(850, -500));
	camera.draw_texture(font50(U"仮"), camera.get_center().movedBy(850, -440));


}
