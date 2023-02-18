﻿#include "OptionShirous.h"
#include"OptionShirousShot.h"
#include"Battle.h"



OptionShirous::OptionShirous(Battle* battle)
	: Option(battle)
{
	set_name(U"シラス");
	set_image_name(U"shirous");
}
OptionShirous::OptionShirous(Battle* battle, Vec2 p)
	: Option(battle, p)
{
	set_name(U"シラス");
	set_image_name(U"shirous");
	option_pos_timer = Random(0, 600);
}


OptionShirous::~OptionShirous()
{

}
void OptionShirous::update(int index)
{
	move(index);
}
void OptionShirous::move(int index)
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

	Vec2 place = battle->get_player().get_pre_pos_left().movedBy(-100 * i + 10 * sin(option_pos_timer / 60.0 / (index + 1)), 30 * i * sin(option_pos_timer / 60.0 / (index + 1)));
	speed += (place - get_pos()) / slowness;
	if (speed.length() > max_speed) speed = speed.normalized() * max_speed;

	prev_pos = pos;
	pos += speed;

	speed /= 1.1;

}
void OptionShirous::move_intersect_stage(Stage_object stage)
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
void  OptionShirous::check_limit_stage(myCamera camera)
{
	if (camera.get_limit_stage_min().y > get_pos_top().y)set_pos_top(camera.get_limit_stage_min().y);
	if (camera.get_limit_stage_max().y < get_pos_bottom().y)set_pos_bottom(camera.get_limit_stage_max().y);
	if (camera.get_limit_stage_min().x > get_pos_left().x)set_pos_left(camera.get_limit_stage_min().x);
	if (camera.get_limit_stage_max().x < get_pos_right().x)set_pos_right(camera.get_limit_stage_max().x);
}


bool OptionShirous::ready_shot()
{
	if (shot_timer > 0)shot_timer--;
	if (shot_timer == 0) return true;
	return false;
}

std::shared_ptr<Shot> OptionShirous::shot()
{
	shot_timer = shot_cool_time;
	//return std::make_shared<OptionShot>(battle,get_pos_right() );
	return std::make_shared<OptionShirousShot>(battle, this);
}


void OptionShirous::draw()
{
	myCamera& camera = battle->get_camera();
	// 自機の描画
	//TextureAsset(name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
	TextureAsset(image_name).scaled(camera.get_scale()).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale(), Palette::Gray);
	font(ID).drawAt(Scene::CenterF() + (get_pos() - camera.get_center()) * camera.get_scale());
}
void OptionShirous::draw_back()
{

}
void OptionShirous::draw_front()
{

}
