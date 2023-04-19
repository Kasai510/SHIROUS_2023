#include "stdafx.h"
#include "EnemyOpabinia.h"
#include"EnemyShotOpabinia.h"
#include"Battle.h"


EnemyOpabinia::EnemyOpabinia(Battle* battle, const Vec2& p):Enemy(battle,p)
{
	image_name = U"opabinia";
	image_size_int = 300;
	speed = { -15,0 };
	width = 220;
	height = 90;
	hp = 100;

	find_player = false;
	mouth_local_pos = { -150,50 };
	mouth_go_local_pos = { -150,50 };
	mouth_v = {0,0};
	mouth_is_open = false;
	is_doing_attack = false;
	attack_from_down = true;
	attack_point_count = 0;
	attack_start_time = 0;
	double theta = Math::Pi * 4 / 5.0;
	for (int8 i : step(5)) {
		attack_points << Vec2{ cos(theta), sin(theta) }*150;
		theta += Math::HalfPi / 6;
	}

	enemy_kind = enemy_kind_opabinia;
}

void EnemyOpabinia::update()
{
	if (!active)
	{
		if (battle->get_camera().in_camera(get_pos()))active = true;
	}
	if (active)
	{
		if (find_player) {
			move();
		}

		if (battle->get_player().get_pos().x - pos.x < -200 and not find_player) {
			find_player = true;
		}
		if (hp <= 0) {
			dead = true;
			drop_item();
		}
		time++;
	}
	
}


void EnemyOpabinia::move()
{
	if ((time % 60) == 0 and not is_doing_attack) {
		mouth_go_local_pos = RandomVec2(Rect{-170,0,50,100});
	}

	if ((time % 250) == 0) {
		is_doing_attack = true;
		attack_start_time = 0;
	}

	if (is_doing_attack) {
		//Print <<U"atac:" << Min(attack_start_time / 30, 4);
		if (attack_from_down) {
			mouth_go_local_pos = attack_points[Min(attack_start_time / 30, 4)];
		}
		else {
			mouth_go_local_pos = attack_points[4-Min(attack_start_time / 30, 4)];
		}
		if (attack_start_time % 30 == 29) {
			battle->get_ememy_shots() << std::make_shared<EnemyShotOpabinia>(battle, pos+mouth_local_pos);
		}
		if (attack_start_time > 160) {
			is_doing_attack = false;
			attack_from_down = not attack_from_down;
		}
		attack_start_time++;

	}

	if (is_doing_attack) {
		mouth_v += (mouth_go_local_pos - mouth_local_pos) * 0.006;
	}
	else {
		mouth_v += (mouth_go_local_pos - mouth_local_pos) * 0.002;
	}
	
	mouth_v *= 0.9;
	mouth_local_pos += mouth_v;

	speed *= 0.9;
	prev_pos = pos;
	pos += speed;
}

void EnemyOpabinia::draw()
{
	myCamera& camera = battle->get_camera();

	Transformer2D tf{ camera.get_mat() };
	get_rect().draw(Palette::Orange);
	//RectF{ -170,0,50,100 }.movedBy(pos).draw();
	//Circle(mouth_go_local_pos + pos, 10).draw(Palette::Red);
	TextureAsset(image_name).resized(image_size_int).drawAt(pos);
	Vec2 pos_head= pos + Vec2{ -100,25 };
	Vec2 pos_mouth = pos + mouth_local_pos;
	Bezier3 hose{ pos_head, pos_head + Vec2{ -20,20 }, pos_mouth + Vec2{ 20,-20 }, pos_mouth };
	hose.draw(LineStyle::RoundCap, 12, Color(0));
	hose.draw(LineStyle::RoundCap, 10, Color(129, 191, 82));

	if (is_doing_attack) {
		TextureAsset(U"opabinia_mouth_open").resized(image_size_int).drawAt(pos + mouth_local_pos);
	}
	else {
		TextureAsset(U"opabinia_mouth_close").resized(image_size_int).drawAt(pos + mouth_local_pos);
	}
	battle->getFont30()(hp).drawAt(pos);

	/*for (auto p : attack_points) {
		Circle{ pos + p,10 }.draw(Palette::Red);
	}*/

}
