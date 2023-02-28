#include "stdafx.h"
#include "EnemyKurage.h"
#include "Battle.h"
#include"myIEffectBubble.h"

EnemyKurage::EnemyKurage(Battle* battle,const Vec2& p):Enemy(battle,p)
{
	image_name = U"kurage";
	image_size_int = 300;
	speed = { 0,0 };
	width = 150;
	height = 150;
	first_level = pos.y;
}

void EnemyKurage::update()
{
	
	move();
	if (hp <= 0) {
		dead = true;
	}
	time++;
}

void EnemyKurage::move()
{
	if (jump_wait_time == 120) {
		jump_wait_time = 0;
		speed.y += (first_level - pos.y)*0.1;
		if (isGoRight) {
			speed.x += 4;
		}
		else {
			speed.x += -4;
		}
		for (int i : step(10)) {
			battle->get_effects() << std::make_unique<myIEffectBubble>(battle, RandomVec2(get_rect()), Random() * 5);

		}
		isGoRight = not isGoRight;
	}
	jump_wait_time++;

	speed.y += 0.1;
	speed *= 0.9;
	prev_pos = pos;
	pos += speed;
}

void EnemyKurage::draw()
{
	
	myCamera& camera = battle->get_camera();
	//camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(TextureAsset(image_name).resized(image_size_int), pos);
	
}
