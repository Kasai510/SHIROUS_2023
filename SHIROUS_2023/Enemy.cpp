#include "stdafx.h"
#include "Enemy.h"
#include"Battle.h"

Enemy::Enemy(Battle* battle,const Vec2& p):Fish(battle,p)
{
	image_size_int = 300;
	hp = 50;
	spon_pos = p;
}

void Enemy::update()
{
	if (!active)
	{
		if (battle->get_camera().in_camera(get_pos()))active = true;
	}
	if (active)
	{
		move();
		if (hp <= 0) {
			dead = true;
			drop_item();
		}
		time++;
	}
	
}

void Enemy::draw()
{
	myCamera& camera = battle->get_camera();
	//camera.draw_texture(get_rect(), Palette::Orange);
	camera.draw_texture(TextureAsset(image_name).resized(image_size_int), pos);
}

void Enemy::move_intersect_stage(Stage_object stage)
{
	if (get_rect().intersects(stage.get_rect()))
	{
		double dx = get_pos().x - stage.get_pos().x;

		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y)
		{
			set_pos_top(stage.get_bottom());
		}
		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y)
		{
			set_pos_bottom(stage.get_top());
		}
		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y)
		{
			set_pos_left(stage.get_right());
		}
		if (stage.get_pre_pos().y + dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) < get_pre_pos().y
			&& stage.get_pre_pos().y - dx / (get_width() + stage.get_width()) * (get_height() + stage.get_height()) > get_pre_pos().y)
		{
			set_pos_right(stage.get_left());
		}

	}
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

