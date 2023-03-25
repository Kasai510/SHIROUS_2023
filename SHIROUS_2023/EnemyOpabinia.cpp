#include "stdafx.h"
#include "EnemyOpabinia.h"
#include"Battle.h"

EnemyOpabinia::EnemyOpabinia(Battle* battle, const Vec2& p):Enemy(battle,p)
{
	image_name = U"opabinia";
	image_size_int = 300;
	speed = { -5,0 };
	width = 250;
	height = 90;
	mouth_pos = { -150,50 };
}

void EnemyOpabinia::update()
{
	if (!active)
	{
		if (battle->get_camera().in_camera(get_pos()))active = true;
	}
	if (active)
	{
		move();
		if (hp <= 0) {
			dead = true;
			drop_item();
		}
		time++;
	}
	
}

void EnemyOpabinia::move()
{
	speed *= 0.9;
	prev_pos = pos;
	pos += speed;
}

void EnemyOpabinia::draw()
{
	myCamera& camera = battle->get_camera();

	Transformer2D tf{ camera.get_mat() };
	//camera.draw_texture(get_rect(), Palette::Orange);
	TextureAsset(image_name).resized(image_size_int).drawAt(pos);
	Bezier3(pos + Vec2{ -100,25 }, pos + Vec2{ -10,10 } + Vec2{ -100,25 }, pos + mouth_pos + Vec2{ 10,-10 }, pos + mouth_pos).draw(LineStyle::RoundCap, 12, Color(0));
	Bezier3(pos + Vec2{ -100,25 }, pos + Vec2{ -10,10 } + Vec2{ -100,25 }, pos + mouth_pos + Vec2{ 10,-10 }, pos + mouth_pos).draw(LineStyle::RoundCap, 10, Color(129, 191, 82));
	
	TextureAsset(U"opabinia_mouth_close").resized(image_size_int).drawAt(pos + mouth_pos);
	battle->getFont30()(hp).drawAt(pos);

}
