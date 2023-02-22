#include "stdafx.h"
#include "EnemyPikaia.h"
#include"EnemyShotPikaia.h"
#include"Battle.h"

EnemyPikaia::EnemyPikaia(Battle* battle,Vec2 p):Enemy(battle, p)
{
	image_name = U"pikaia";
	image_size_int = 300;
	speed = { -5,0 };
	width = 250;
	height = 90;
	time.restart();
	anime << TextureAsset(U"pikaia_1").resized(image_size_int);
	anime << TextureAsset(U"pikaia_2").resized(image_size_int);
	anime << TextureAsset(U"pikaia_3").resized(image_size_int);
	anime << TextureAsset(U"pikaia_2").resized(image_size_int);
	delays = Array<int32>{ 320,320,320,320 };
}

void EnemyPikaia::update()
{
	
	move();
	{
		double r_player = (battle->get_player().get_pos() - pos).length();
		if (r_player <1000) {
			battle->get_ememy_shots()<< std::make_shared<EnemyShotPikaia>(battle, pos,shared_from_this());
			dead = true;
		}
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
	camera.draw_texture(get_rect(), Palette::Orange);
	//camera.draw_texture(Circle{pos,45}, Palette::Red);
	camera.draw_texture(anime[AnimatedGIFReader::GetFrameIndex(time.sF(), delays)], pos);
}

