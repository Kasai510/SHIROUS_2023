#include "stdafx.h"
#include "EnemyHallucigenia.h"
#include"Battle.h"

EnemyHallucigenia::EnemyHallucigenia(Battle* battle,const Vec2& p) :Enemy(battle, p)
{
	image_name = U"hallucigenia";
	image_size_int = 150;
	speed = { 0,0 };
	width = 120;
	height = 90;
}

void EnemyHallucigenia::update()
{
	move();
	if (pos.y > 1500) {
		dead = true;
	}
	if (hp <= 0) {
		dead = true;
	}
	time++;
}

void EnemyHallucigenia::move()
{
	speed = pos - prev_pos;
	speed.x = Max(-5.0, speed.x - 1);
	speed.y += 1;

	prev_pos = pos;
	pos += speed;
}

void EnemyHallucigenia::draw()
{
	myCamera& camera = battle->get_camera();
	camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(TextureAsset(image_name).resized(image_size_int), pos);
}
