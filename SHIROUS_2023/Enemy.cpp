#include "stdafx.h"
#include "Enemy.h"
#include"Battle.h"

Enemy::Enemy(Battle* battle,const Vec2& p):Fish(battle,p)
{
	image_size_int = 300;
	hp = 50;
}

void Enemy::update()
{
	move();
	if (hp <= 0) {
		dead = true;
		drop_item();
	}
	time++;
}

void Enemy::draw()
{
	myCamera& camera = battle->get_camera();
	//camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(TextureAsset(image_name).resized(image_size_int), pos);
}

void Enemy::move()
{
	prev_pos = pos;
	if (speed.length() > 1.0)pos += max_speed * speed.normalized();
	else pos += max_speed * speed;
}


void  Enemy::drop_item()
{
	drop_LP();
}
void  Enemy::drop_LP()
{
	for (int i = 0; i < 5; i++)
	{
		battle->get_items() << std::make_shared<ItemLP>(battle, get_pos(), 10);
	}
}

