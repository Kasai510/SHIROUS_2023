#include "stdafx.h"
#include "Enemy.h"
#include"Battle.h"

Enemy::Enemy(Battle* battle, Vec2 p):Fish(battle,p)
{
	image_size_int = 300;
}

void Enemy::draw()
{
	battle->get_camera().draw_texture(TextureAsset(image_name).resized(image_size_int),pos);
	
}

