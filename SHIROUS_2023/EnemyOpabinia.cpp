#include "stdafx.h"
#include "EnemyOpabinia.h"
#include"Battle.h"

EnemyOpabinia::EnemyOpabinia(Battle* battle, const Vec2& p):Enemy(battle,p)
{
	image_name = U"opabinia";
	image_size_int = 300;
	speed = { -15,0 };
	width = 220;
	height = 90;
	mouth_local_pos = { -150,50 };
	mouth_go_local_pos = { -150,50 };
	mouth_v = {0,0};
	mouth_is_open = false;
}

void EnemyOpabinia::update()
{
	move();
	if (hp <= 0) {
		dead = true;
	}
	time++;
}

void EnemyOpabinia::move()
{
	if ((time %= 60) == 0) {
		mouth_go_local_pos = RandomVec2(Rect{-170,0,50,100});
	}

	mouth_v += (mouth_go_local_pos - mouth_local_pos) * 0.002;
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
	
	TextureAsset(U"opabinia_mouth_close").resized(image_size_int).drawAt(pos + mouth_local_pos);
	battle->getFont30()(hp).drawAt(pos);

}
