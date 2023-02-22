#include "stdafx.h"
#include "Enemy.h"
#include"Battle.h"

Enemy::Enemy(Battle* battle, Vec2 p):Fish(battle,p)
{
	image_size_int = 300;
}

void Enemy::update()
{
	move();
	time++;
}

void Enemy::draw()
{
	myCamera& camera = battle->get_camera();
	camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(TextureAsset(image_name).resized(image_size_int), pos);
}

void Enemy::move()
{
	prev_pos = pos;
	if (speed.length() > 1.0)pos += max_speed * speed.normalized();
	else pos += max_speed * speed;
}

void Enemy::damage(double d)
{
	hp -= d;
}

