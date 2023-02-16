#include "stdafx.h"
#include "Enemy.h"
#include"Battle.h"

Enemy::Enemy(Battle* battle, Vec2 p):Fish(battle,p)
{
	image_size_int = 300;
}

void Enemy::draw()
{
	myCamera& camera = battle->get_camera();
	TextureAsset(image_name).resized(image_size_int).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
}

