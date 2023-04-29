#include"Battle.h"
#include"EnemyPikaia.h"
#include"EnemyKurage.h"
#include"EnemyShotPikaia.h"
#include"EnemyHallucigenia.h"
#include"EnemyOpabinia.h"
#include"EnemyAnomalocaris.h"

void Battle::init_map_make()
{
	for (int i = 0; i < 4; i++)
	{
		Vec2 center_pos = Vec2{1700,600}+90 * Vec2{ cos(-90_deg+90_deg * i),sin(-90_deg + 90_deg * i) };
		change_object_scale_box[i] = RectF(Arg::center(center_pos), 80, 80);
	}

	enemies.clear();
	player_shots.clear();
	enemy_shots.clear();
	effects.clear();
	items.clear();

	initialize_enemies();//これはのちにEnemiesManagerとかがするかも知れない
}

void Battle::update_map_make()
{
	cursor_window_pos = camera.windowpos_in_camera(Cursor::Pos());

	if (KeyM.down())
	{
		//battle
		change_battle_scene(Battle_Scene::battle);
	
	}

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
		save();
	}

	//置くオブジェクトの種類の変更
	if (KeyA.down())
	{
		now_put_enemies = not now_put_enemies;
	}


	if (now_put_enemies)
	{
		update_map_make_put_enemy();
	}
	else
	{
		update_map_make_put_stage_object();
	}


}

void Battle::update_map_make_put_enemy()
{

	//敵の配置

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
	if (KeyD.down())
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

}

void Battle::update_map_make_put_stage_object()
{
	if (KeySpace.down())
	{
		stages << Stage_object(this,cursor_window_pos, put_object_width, put_object_height);
	}

	if (KeyD.down())
	{
		for (auto& stage : stages)
		{
			if (stage.get_width() <= 10000)
			{
				if (stage.get_rect().intersects(Circle(cursor_window_pos, 1)))
				{
					stage.set_exist(false);
					break;
				}
			}
		}

		stages.remove_if([](Stage_object stage)
			{
				return stage.get_exist() == false;
		});
	}

	for (int i = 0; i < 4; i++)
	{
		

		//置くobjectの選択
		if (change_object_scale_box[i].leftPressed())
		{
			switch (i)
			{
			case 0:
				put_object_height += 1;
				break;
			case 1:
				put_object_width += 1;
				break;
			case 2:
				put_object_height -= 1;
				break;
			case 3:
				put_object_width -= 1;
				break;
			default:
				break;
			}
		}

	
	}
}


void Battle::draw_map_make()
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
	for (auto& item : items) {
		item->draw();
	}


	camera.draw_stage_area();

	font50(U"[M]で終了").draw(0, 0, Palette::Black);
	font50(U"[S]でsave").draw(0, 60, Palette::Black);
	

	if (now_put_enemies)
	{
		draw_map_make_put_enemy();
	}
	else
	{
		draw_map_make_put_stage_object();
	}

}

void Battle::draw_map_make_put_enemy()
{
	font50(U"[A]でオブジェクト配置に変更").draw(0, 120, Palette::Black);
	font50(U"[Space]で敵を配置").draw(0, 190, Palette::Black);
	font50(U"[D]で敵を削除").draw(0, 250, Palette::Black);
	font50(U"[C]で配置する敵の種類を変更").draw(0, 310, Palette::Black);


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

void Battle::draw_map_make_put_stage_object()
{
	font50(U"[A]で敵配置に変更").draw(0, 120, Palette::Black);
	font50(U"[Space]で配置").draw(0, 180, Palette::Black);
	font50(U"[D]でオブジェクトの削除").draw(0, 240, Palette::Black);


	font90(U"→").drawAt(1710, 610,Palette::Black);
	font90(U"↑").drawAt(1700, 590, Palette::Black);

	for(int i = 0; i < 4; i++)
	{
		change_object_scale_box[i].draw(Palette::Black);
		if (i == 0 || i == 1)
		{
			font50(U"＋").drawAt(change_object_scale_box[i].center(), Palette::White);
		}
		else
		{
			font50(U"－").drawAt(change_object_scale_box[i].center(), Palette::White);
		}
	}

	

	RectF put_rect{ Arg::center(cursor_window_pos),put_object_width,put_object_height };
	camera.draw_texture(put_rect, HSV(0,0,0,0.7));
	camera.draw_textureframe(put_rect,2, Palette::Red);


	RectF stage_tex_box(1700, 200, 200, 200);
	stage_tex_box.draw(HSV(0, 0, 0, 0.7));
	RectF(Arg::center(stage_tex_box.center()), 180, 180).draw(Palette::Blue);

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
		enemy_datas.clear();

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

void Battle::initialize_stage_object()
{

	
	// 読み込み先のデータ
	
	{
		// バイナリファイルをオープン
		String fail_name = U"data/binary/Stage_Data/Stage{}/Stage_object_Data.bin"_fmt(stage_index);
		Deserializer<BinaryReader> reader{ fail_name };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open `stage_object_data.bin`" };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）

		stage_object_datas.clear();
		reader(stage_object_datas);


		// reader のデストラクタで自動的にファイルがクローズされる
	}

	stages.clear();
	for (auto& stage_object_data : stage_object_datas)
	{
		stages << Stage_object(this, stage_object_data.spon_pos, stage_object_data.width, stage_object_data.height);
	}
	
}


void Battle::save_stage_object()
{
	{

		// 記録したいデータ

		stage_object_datas.clear();
		for (auto& stage : stages)
		{
			stage_object_datas << Stage_object_Data(stage.get_pos(), stage.get_width(),stage.get_height());
		}

		// バイナリファイルをオープン

		String fail_name = U"data/binary/Stage_Data/Stage{}/Stage_object_Data.bin"_fmt(stage_index);

		Serializer<BinaryWriter> writer{ fail_name };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open `enemy_data.bin`" };
		}


		// シリアライズに対応したデータを記録

		writer(stage_object_datas);

		// writer のデストラクタで自動的にファイルがクローズされる

	}

}


