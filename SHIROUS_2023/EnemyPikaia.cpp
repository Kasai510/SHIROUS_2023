#include "stdafx.h"
#include "EnemyPikaia.h"
#include"Battle.h"

EnemyPikaia::EnemyPikaia(Battle* battle,Vec2 p):Enemy(battle, p)
{
	image_name = U"pikaia";
	image_size_int = 300;
	speed = { -1,0 };
	width = 250;
	height = 90;
	time.restart();
	anime << TextureAsset(U"pikaia_1").resized(image_size_int);
	anime << TextureAsset(U"pikaia_2").resized(image_size_int);
	anime << TextureAsset(U"pikaia_3").resized(image_size_int);
	anime << TextureAsset(U"pikaia_2").resized(image_size_int);
}

void EnemyPikaia::update()
{
	
	move();
	if (KeyW.pressed()) {
		speed.rotate(0.01);
	}
	if (KeyS.pressed()) {
		speed.rotate(-0.01);
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
	camera.draw_texture(Circle{ pos,45 }, Palette::Red);
	camera.draw_texture(anime[AnimatedGIFReader::GetFrameIndex(time.sF(), Array<int32>{400,400,400,400})], pos);
}

