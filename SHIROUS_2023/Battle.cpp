#include"Battle.h"
#include"EnemyPikaia.h"
#include"EnemyKurage.h"
#include"EnemyShotPikaia.h"
#include"EnemyHallucigenia.h"
#include"EnemyOpabinia.h"
#include"EnemyAnomalocaris.h"


Battle::Battle()
{

	//stages << Stage_object(this,{ 800,600 }, 200, 200);
	//stages << Stage_object(this, { 1400,600 }, 200, 200);
	stages << Stage_object(this, { -100,1000 , 19200+200, 200 });
	initialize_enemies();//これはのちにEnemiesManagerとかがするかも知れない
}

Battle::~Battle()
{
	save_enemies();
}

void Battle::update()
{
	if (KeyM.down())
	{
		//map_make
		now_map_make = not now_map_make;
	}




	scene_del = Scene::DeltaTime();

	if (now_map_make)
	{
		update_map_make();
	}
	else
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
		enemies.remove_if([](const std::shared_ptr<Enemy>& enemy) {return enemy->is_dead(); });

		//camera.scroll(Vec2(2,0));//強制横スクロール
		camera.set(player.get_pos());

		//for debug
		camera_control();
	}
}

void Battle::update_map_make()
{
	//カメラの上下左右移動
	if (KeyRight.pressed())
	{
		camera.set_center(camera.get_center() + Vec2{ 10,0 });
	}
	if (KeyLeft.pressed())
	{
		camera.set_center(camera.get_center() + Vec2{ -10,0 });
	}
	if (KeyUp.pressed())
	{
		camera.set_center(camera.get_center() + Vec2{ 0,-10 });
	}
	if (KeyDown.pressed())
	{
		camera.set_center(camera.get_center() + Vec2{ 0,10 });
	}

	camera.calc_mat();

	//Save
	if (KeyS.down())
	{
		save_enemies();
	}

	//配置する敵の変更
	if (KeyC.down())
	{
		if (select_enemy_kind + 1 == enemy_kind_num)
		{
			select_enemy_kind = Enemy_Kind(0);
		}
		else
		{
			select_enemy_kind = Enemy_Kind(select_enemy_kind + 1);
		}

	}

	//敵の配置
	Vec2 cursor_window_pos = camera.windowpos_in_camera(Cursor::Pos());
	if (KeySpace.down())
	{
		
		
		switch (Enemy_Kind(select_enemy_kind))
		{
		case enemy_kind_pikaia:
			enemies << std::make_shared<EnemyPikaia>(this, cursor_window_pos);
			break;
		case enemy_kind_opabinia:
			enemies << std::make_shared<EnemyOpabinia>(this, cursor_window_pos);
			break;
		case enemy_kind_kurage:
			enemies << std::make_shared<EnemyKurage>(this, cursor_window_pos);
			break;
		case enemy_kind_hallucigenia:
			enemies << std::make_shared<EnemyHallucigenia>(this, cursor_window_pos);
			break;
		case enemy_kind_anomalocaris:
			enemies << std::make_shared<EnemyAnomalocaris>(this, cursor_window_pos);
			break;
		default:
			break;
		}
	}


	//敵の削除
	if (MouseL.down())
	{
		enemies.remove_if([&](const std::shared_ptr<Enemy>& enemy)
			{

					if (enemy->get_rect().intersects(Circle(cursor_window_pos, 2)))
					{
						return true;
					}
					return false;
		});
	}
}

void Battle::draw_map_make()
{
	font30(U"[M]で終了").draw(0, 0, Palette::Black);
	font30(U"[S]でsave").draw(0, 200, Palette::Black);
	font30(U"[Space]で敵を配置").draw(0, 250, Palette::Black);
	font30(U"[左クリック]で敵を削除").draw(0, 300, Palette::Black);
	font30(U"[C]で配置する敵の種類を変更").draw(0, 350, Palette::Black);

	String select_enemy_name;
	switch (Enemy_Kind(select_enemy_kind))
	{
	case enemy_kind_pikaia:
		select_enemy_name = U"pikaia";
		break;
	case enemy_kind_opabinia:
		select_enemy_name = U"opabinia";
		break;
	case enemy_kind_kurage:
		select_enemy_name = U"kurage";
		break;
	case enemy_kind_hallucigenia:
		select_enemy_name = U"hallucigenia";
		break;
	case enemy_kind_anomalocaris:
		select_enemy_name = U"anomalocaris";
		break;
	default:
		break;
	}

	RectF enemy_tex_box(1700, 200, 200, 200);
	enemy_tex_box.draw(HSV(0, 0, 0, 0.7));
	TextureAsset(select_enemy_name).resized(180).drawAt(enemy_tex_box.center());

}

void Battle::draw()
{


	//背景
	background.draw();

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

	
	
	camera.draw_stage_area();

	draw_UI();
	debug_draw();
}
void Battle::draw_UI()
{
	camera.draw_texture(RectF{ Arg::center(camera.get_center().movedBy(0,-465)),1920,150 }, Palette::Black);
	camera.draw_texture(font30(U"HP"), camera.get_center().movedBy(-1920 / 2 + 50, -500));
	camera.draw_texture(font30(U"LP"), camera.get_center().movedBy(-1920 / 2 + 50, -430));

	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -500), player.get_HP(), 20 }, Palette::Lightgreen);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -430), player.get_Max_LP(), 20 }, Palette::Gray);
	camera.draw_texture(RectF{ camera.get_center().movedBy(-1920 / 2 + 100, -430), player.get_LP(), 20 }, Palette::Lightgreen);


	if (now_map_make)
	{
		draw_map_make();
	}
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
	
	// 読み込み先のデータ
	{
		// バイナリファイルをオープン
		String fail_name = U"data/binary/Stage_Data/Stage{}/Enemy_Data.bin"_fmt(stage_index);
		Deserializer<BinaryReader> reader{ fail_name };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open `enemy_data.bin`" };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）

	
		reader(enemy_datas);


		// reader のデストラクタで自動的にファイルがクローズされる
	}

	for (auto& enemy_data : enemy_datas)
	{

		switch (Enemy_Kind(enemy_data.enemy_kind))
		{
		case enemy_kind_pikaia:
			enemies << std::make_shared<EnemyPikaia>(this, enemy_data.spon_pos);
			break;
		case enemy_kind_opabinia:
			enemies << std::make_shared<EnemyOpabinia>(this, enemy_data.spon_pos);
			break;
		case enemy_kind_kurage:
			enemies << std::make_shared<EnemyKurage>(this, enemy_data.spon_pos);
			break;
		case enemy_kind_hallucigenia:
			enemies << std::make_shared<EnemyHallucigenia>(this, enemy_data.spon_pos);
			break;
		case enemy_kind_anomalocaris:
			enemies << std::make_shared<EnemyAnomalocaris>(this, enemy_data.spon_pos);
			break;
		default:
			break;
		}

	}
}

void Battle::save_enemies()
{
	
	{
		
		// 記録したいデータ
		
		enemy_datas.clear();
		for (auto& enemy : enemies)
		{

			enemy_datas << Enemy_Data(enemy->get_enemy_kind(), enemy->get_spon_pos());
		}

		// バイナリファイルをオープン

		String fail_name = U"data/binary/Stage_Data/Stage{}/Enemy_Data.bin"_fmt(stage_index);

		Serializer<BinaryWriter> writer{ fail_name };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open `enemy_data.bin`" };
		}


		// シリアライズに対応したデータを記録
		
		writer(enemy_datas);	

		// writer のデストラクタで自動的にファイルがクローズされる
		
	}

}

void Battle::add_draw_objects(std::shared_ptr<BattleObject>)
{
	//draw_order順に配列に組み込まれるような処理
}
