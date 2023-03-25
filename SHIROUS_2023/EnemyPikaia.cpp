#include "stdafx.h"
#include "EnemyPikaia.h"
#include"EnemyShotPikaia.h"
#include"Battle.h"

EnemyPikaia::EnemyPikaia(Battle* battle,const Vec2& p):Enemy(battle, p)
{
	image_name = U"pikaia";
	image_size_int = 300;
	speed = { -5,0 };
	width = 250;
	height = 90;
	anime << TextureAsset(U"pikaia_1").resized(image_size_int);
	anime << TextureAsset(U"pikaia_2").resized(image_size_int);
	anime << TextureAsset(U"pikaia_3").resized(image_size_int);
	anime << TextureAsset(U"pikaia_2").resized(image_size_int);
	delays = Array<int32>{ 320,320,320,320 };


	//TAKEがかいた（消してもいい）
	hp = 10;
}

void EnemyPikaia::update()
{
	if (!active)
	{
		if (battle->get_camera().in_camera(get_pos()))active = true;
		
	}
	if (active)
	{
		move();
		{
			double r_player = (battle->get_player().get_pos() - pos).length();
			if (r_player < 1000) {
				battle->get_ememy_shots() << std::make_shared<EnemyShotPikaia>(battle, pos);
				dead = true;
			}
		}
		if (hp <= 0) {
			dead = true;
			drop_item();
		}
		time++;
	}
	
}

void EnemyPikaia::move()
{
	prev_pos = pos;
	pos += speed;
}

void EnemyPikaia::draw()
{
	myCamera& camera = battle->get_camera();
	//camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(anime[AnimatedGIFReader::GetFrameIndex(time/60.0, delays)], pos);
}

