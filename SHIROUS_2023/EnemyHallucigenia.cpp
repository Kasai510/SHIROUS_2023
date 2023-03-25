#include "stdafx.h"
#include "EnemyHallucigenia.h"
#include"EnemyShotHallucigenia.h"
#include"myIEffectCirclestar.h"
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
	if (!active)
	{
		if (battle->get_camera().in_camera(get_pos()))active = true;
	}
	if (active)
	{
		move();
		{
			double r_player = abs(battle->get_player().get_pos().x - pos.x);
			if (r_player < 100) {
				battle->get_ememy_shots() << std::make_shared<EnemyShotHallucigenia>(battle, pos + Vec2{ 0,-10 });
				battle->get_effects() << std::make_unique<myIEffectCirclestar>(battle, pos + Vec2{ 0,-10 }, 70);
				dead = true;
			}
		}
		if (pos.y > 1500) {
			dead = true;
		}
		if (hp <= 0) {
			dead = true;
			drop_item();
		}
		time++;
	}
	
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
	//camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(TextureAsset(image_name).resized(image_size_int), pos);
}
