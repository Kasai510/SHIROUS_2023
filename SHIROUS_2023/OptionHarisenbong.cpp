﻿#include "stdafx.h"
#include "OptionHarisenbong.h"
#include"OptionHarisenbongShot.h"
#include"Battle.h"




OptionHarisenbong::OptionHarisenbong(Battle* battle)
	: Option(battle)
{
	set_name(U"ハリセンボン");
	set_image_name(U"harisenbong");


	width = 100;
	height = 100;
	shot_cool_time = 90;
	shot_timer = shot_cool_time;
}
OptionHarisenbong::OptionHarisenbong(Battle* battle, Vec2 p)
	: Option(battle, p)
{
	set_name(U"ハリセンボン");
	set_image_name(U"harisenbong");
	option_pos_timer = Random(0, 600);

	width = 100;
	height = 100;
	shot_cool_time = 90;
	shot_timer = shot_cool_time;
}


OptionHarisenbong::~OptionHarisenbong()
{

}
void OptionHarisenbong::update(int index)
{
	move(index);
	attack();

}
void OptionHarisenbong::move(int index)
{
	option_pos_timer++;
	if (option_pos_timer > 2 * Math::Pi * 60 * (index + 1))option_pos_timer -= 2 * Math::Pi * 60 * (index + 1);

	double slowness = 100.0;

	int i = 1;
	int j = 0;
	while (j < index)
	{
		i++;
		j += i;
	}

	place = battle->get_player().get_pre_pos_left().movedBy(-100 * i + 10 * sin(option_pos_timer / 60.0 / (index + 1)), 30 * i * sin(option_pos_timer / 60.0 / (index + 1)));
	speed += (place - get_pos()) / slowness;
	if (speed.length() > max_speed) speed = speed.normalized() * max_speed;

	prev_pos = pos;
	pos += speed;

	speed /= 1.1;

}
void OptionHarisenbong::move_intersect_stage(Stage_object stage)
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
void  OptionHarisenbong::check_limit_stage(myCamera camera)
{
	if (camera.get_limit_stage_min().y > get_pos_top().y)set_pos_top(camera.get_limit_stage_min().y);
	if (camera.get_limit_stage_max().y < get_pos_bottom().y)set_pos_bottom(camera.get_limit_stage_max().y);
	if (camera.get_limit_stage_min().x > get_pos_left().x)set_pos_left(camera.get_limit_stage_min().x);
	if (camera.get_limit_stage_max().x < get_pos_right().x)set_pos_right(camera.get_limit_stage_max().x);
}


bool OptionHarisenbong::ready_shot()
{
	if (shot_timer > 0 && optionshots.size() == 0)shot_timer--;

	if (shot_timer == 0)
	{
		shot_timer = shot_cool_time;
		return true;
	}
	return false;
}

void OptionHarisenbong::attack()
{
	//攻撃の更新
	for (int i = 0; i < optionshots.size(); i++)
	{
		optionshots[i]->update();

	}


	optionshots.remove_if([](const std::shared_ptr<Shot> p) {return (p->get_over()); });


	if (ready_shot())
	{
		for (int i = 0; i <= 5; i++)
		{
			optionshots << std::make_shared<OptionHarisenbongShot>(battle, shared_from_this(),60_deg*i);
		}
	}
}



void OptionHarisenbong::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	//TextureAsset(name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());

	//当たり判定の描画
	battle->get_camera().draw_texture(get_rect(), Palette::Red);

	TextureAsset(image_name).resized(width).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
	font(shot_timer).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());

	//攻撃の描画
	for (int i = 0; i < optionshots.size(); i++)
	{
		optionshots[i]->draw();

	}
}
void OptionHarisenbong::draw_back()
{

}
void OptionHarisenbong::draw_front()
{

}